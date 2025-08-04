#include "exec.h"
#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


static int  child_exec(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd)
{
    char    *path;
    char    **envp;

    if (in_fd != STDIN_FILENO)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO)
    {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
    if (is_builtin(cmd))
    {
        int status = execute_builtin(cmd, shell);
        exit(status);
    }
    path = resolve_command_path(cmd->argv[0], shell->env);
    envp = env_to_str_array(shell->env);
    if (!path)
    {
        fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
        if (envp)
        {
            int i = 0; while (envp[i]) free(envp[i++]); free(envp);
        }
        exit(127);
    }
    execve(path, cmd->argv, envp);
    perror(cmd->argv[0]);
    if (envp)
    {
        int i = 0; while (envp[i]) free(envp[i++]); free(envp);
    }
    free(path);
    exit(126);
}

int     execute_pipeline(t_cmd *cmds, t_shell *shell)
{
    int     count;
    t_cmd   *tmp;
    int     i;
    int     prev_fd;
    int     pipe_fd[2];
    pid_t   *pids;
    int     status;

    if (!cmds)
        return (0);
    tmp = cmds;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    if (count == 1 && is_builtin(cmds))
    {
        shell->last_exit_code = execute_builtin(cmds, shell);
        return (shell->last_exit_code);
    }
    pids = malloc(sizeof(pid_t) * count);
    if (!pids)
        return (1);
    prev_fd = STDIN_FILENO;
    i = 0;
    while (cmds)
    {
        if (cmds->next)
        {
            if (pipe(pipe_fd) == -1)
                return (free(pids), perror("pipe"), 1);
        }
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (cmds->next)
                close(pipe_fd[0]);
            child_exec(cmds, shell, prev_fd,
                cmds->next ? pipe_fd[1] : STDOUT_FILENO);
        }
        if (prev_fd != STDIN_FILENO)
            close(prev_fd);
        if (cmds->next)
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
        i++;
        cmds = cmds->next;
    }
    if (prev_fd != STDIN_FILENO)
        close(prev_fd);
    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
    free(pids);
    if (WIFEXITED(status))
        shell->last_exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->last_exit_code = 128 + WTERMSIG(status);
    return (shell->last_exit_code);
}