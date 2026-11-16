
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid[4];

    for (int i = 0; i < 4; i++)
    {
        pid[i] = fork();

        if (pid[i] < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid[i] == 0)
        {
            printf("Child %d: PID = %d, PPID = %d\n",
                   i + 1, getpid(), getppid());
            sleep(15);
            exit(0);
        }
    }

    printf("Parent PID = %d\n", getpid());

    for (int i = 0; i < 4; i++)
        wait(NULL);

    printf("All child processes completed.\n");

    return 0;
}

