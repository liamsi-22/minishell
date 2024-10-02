#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    int x;
    int y;

    if (pipe(fd) == -1)
        return 1;

    x = fork();
    if (x < 0)
        return 1;
    // child rocess 1
    if (x == 0)
    {
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls","ls","-la",NULL);
    }
    waitpid(x,NULL,0);
    y = fork();
    if (y < 0)
        return 1;
    if (y == 0)
    {
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep","grep","main",NULL);
    }
    waitpid(x,NULL,0);
    close(fd[0]);
    close(fd[1]);
}