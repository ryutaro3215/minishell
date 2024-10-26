#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


void    err(char *str)
{
    while(*str)
        write(2, str++, 1);
}

int cd(char **argv, int i)
{
    if (i != 2)
    {
        err("error: cd: bad arguments\n");
        return 1;
    }
    if (chdir(argv[1]) == -1)
    {
        err("error: cd: cannot change directory to ");
        err(argv[1]);
        err("\n");
        return 1;
    }
    return 0;
}

int exec(char **argv, int i, char **envp)
{
    int has_pipe = 0;
    int fd[2];
    int pid;
    int status;

    if (argv[i] && !strcmp(argv[i], "|"))
        has_pipe = 1;
    if (!has_pipe && !strcmp(*argv, "cd"))
        return cd(argv, i);
    if (has_pipe && pipe(fd) == -1)
    {
        err("error: fatal\n");
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        err("error: fatal\n");
        exit(1);
    }
    if (!pid)
    {
        argv[i] = 0;
        if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        {
            err("error: fatal\n");
            exit(1);
        }
        if (!strcmp(*argv, "cd"))
            exit(cd(argv, i));
        execve(*argv, argv, envp);
        err("error: cannot execute ");
        err(*argv);
        err("\n");
        exit(1);
    }
    waitpid(pid, &status, 0);
    if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
    {
        err("error: fatal\n");
        exit(1);
    }
    return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
    int i = 0;
    int status = 0;

    while (argv[i])
    {
        argv += i + 1;
        i = 0;
        while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
            i++;
        if (i)
            status = exec(argv, i, envp);
    }
    return status;
}

