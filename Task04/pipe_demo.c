#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        int value, count = 0, sum = 0, max = -1;

        while (read(fd[0], &value, sizeof(value)) > 0)
        {
            count++;
            sum += value;

            if (value > max)
                max = value;
        }

        close(fd[0]);

        printf("Weather Station Analyzer\n");
        printf("Total readings: %d\n", count);

        if (count > 0)
        {
            printf("Average temperature: %.2f\n",
                   (float)sum / count);
            printf("Maximum temperature: %d\n", max);
        }

        printf("Reader done\n");
        exit(0);
    }
    else
    {
        close(fd[0]);

        int readings[] = {32, 35, 38, 41, 34, 33};

        for (int i = 0; i < 6; i++)
            write(fd[1], &readings[i], sizeof(int));

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
