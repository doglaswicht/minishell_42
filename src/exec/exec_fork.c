#include "exec.h"
#include "builtin.h"
#include "redir.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int      **g_pipes;
extern int      g_pipe_count;
extern int      g_exit_code;

pid_t           g_last_pid = -1;

static void     free_envp(char **envp)
{
    int i;

    if (!envp)
        return ;
    i = 0;
    while (envp[i])
        free(envp[i++]);
    free(envp);
}

void    child_process_exec(t_cmd *cmd, t_shell *shell, int is_last)
{
    (void)is_last;
    if (handle_redirections(cmd) < 0)
        exit(1);
    if (is_builtin(cmd))
    {
        int status = execute_builtin(cmd, shell);
        exit(status);
    }
    exit(launch_execve(cmd, shell));
}

int spawn_child_process(t_cmd *cmd, t_shell *shell, int *fds, int is_last)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        handle_exec_error("fork");
        return (-1);
    }
    if (pid == 0)
    {
        if (fds[0] != STDIN_FILENO)
            dup2(fds[0], STDIN_FILENO);
        if (fds[1] != STDOUT_FILENO)
            dup2(fds[1], STDOUT_FILENO);
        close_all_pipes(g_pipes, g_pipe_count);
        child_process_exec(cmd, shell, is_last);
    }
    if (is_last)
        g_last_pid = pid;
    return (pid);
}

int execute_single_command(t_cmd *cmd, t_shell *shell)
{
    pid_t   pid;
    int     status;
    int     fds[2];

    if (!cmd)
        return (0);
    if (is_builtin(cmd))
    {
        shell->last_exit_code = execute_builtin(cmd, shell);
        return (shell->last_exit_code);
    }
    fds[0] = STDIN_FILENO;
    fds[1] = STDOUT_FILENO;
    pid = spawn_child_process(cmd, shell, fds, 1);
    if (pid < 0)
        return (shell->last_exit_code = 1);
    waitpid(pid, &status, 0);
    update_exit_code_from_status(status);
    shell->last_exit_code = g_exit_code;
    return (shell->last_exit_code);
}

int launch_execve(t_cmd *cmd, t_shell *shell)
{
    char    *path;
    char    **envp;
    int     ret;

    path = resolve_command_path(cmd->argv[0], shell->env);
    envp = env_to_str_array(shell->env);
    if (!path)
    {
        fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
        free_envp(envp);
        return (127);
    }
    execve(path, cmd->argv, envp);
    ret = errno;
    handle_exec_error(cmd->argv[0]);
    free(path);
    free_envp(envp);
    if (ret == EACCES)
        return (126);
    return (127);
}