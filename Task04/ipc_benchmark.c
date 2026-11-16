#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int sizes[] = {1, 10, 100};
    char buffer[4096];

    for (int s = 0; s < 3; s++)
    {
        long total = (long)sizes[s] * 1024 * 1024;
        int fd[2];

        pipe(fd);

        pid_t pid = fork();

        if (pid == 0)
        {
            close(fd[1]);

            long received = 0;
            ssize_t n;

            while ((n = read(fd[0], buffer, sizeof(buffer))) > 0)
                received += n;

            close(fd[0]);
            printf("%d MB: Received %ld bytes\n",
                   sizes[s], received);
            exit(0);
        }
        else
        {
            close(fd[0]);

            long sent = 0;
            clock_t start = clock();

            while (sent < total)
            {
                size_t amount = total - sent < sizeof(buffer)
                    ? (size_t)(total - sent) : sizeof(buffer);

                ssize_t n = write(fd[1], buffer, amount);

                if (n <= 0)
                    break;

                sent += n;
            }

            close(fd[1]);
            wait(NULL);

            clock_t end = clock();

            printf("Transfer time: %.4f seconds\n\n",
                   (double)(end - start) / CLOCKS_PER_SEC);
        }
    }

    return 0;
}
