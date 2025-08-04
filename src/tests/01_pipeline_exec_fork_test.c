
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define MAX_CMDS 4

char *test_pipeline[][MAX_CMDS] = {
	{"echo", "hello world", NULL},
	{"ls", "-l", NULL},
	{"grep", ".c", NULL},
	{"wc", "-l", NULL}
};

void fatal(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void run_test_pipeline(void)
{
	int i = 0;
	int pipes[MAX_CMDS - 1][2];
	pid_t pids[MAX_CMDS];

	while (i < MAX_CMDS - 1)
	{
		if (pipe(pipes[i]) == -1)
			fatal("pipe");
		i++;
	}

	for (i = 0; i < MAX_CMDS; i++)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			fatal("fork");

		if (pids[i] == 0)
		{
			// CHILD PROCESS

			if (i > 0)
			{
				if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
					fatal("dup2 stdin");
			}
			if (i < MAX_CMDS - 1)
			{
				if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
					fatal("dup2 stdout");
			}

			// Close all pipe ends in child
			for (int j = 0; j < MAX_CMDS - 1; j++)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}

			execlp(test_pipeline[i][0], test_pipeline[i][0], test_pipeline[i][1], test_pipeline[i][2], NULL);
			fatal("exec");
		}
	}

	// PARENT: Close all pipe ends
	for (i = 0; i < MAX_CMDS - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}

	// Wait all children
	for (i = 0; i < MAX_CMDS; i++)
	{
		int status;
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			printf("[TEST] Child %d exited with code: %d\n", i, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("[TEST] Child %d killed by signal: %d\n", i, WTERMSIG(status));
		else
			printf("[TEST] Unknown termination of child %d\n", i);
	}
}

int main(void)
{
	printf("🧪 [TEST] Running fork + pipeline chain test...\n\n");
	run_test_pipeline();
	printf("\n✅ [TEST COMPLETE] If output makes sense and no leaks => PASS\n");
	return (0);
}