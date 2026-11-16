#include <stdio.h>

#define N 4

int main()
{
    const char *name[N] = {"P1", "P2", "P3", "P4"};
    int arrival[N] = {0, 1, 2, 3};
    int burst[N] = {8, 4, 9, 5};
    int quantum = 20;

    int remaining[N], finish[N];
    int queue[10000];
    int head = 0, tail = 0;
    int added[N] = {0};

    for (int i = 0; i < N; i++)
        remaining[i] = burst[i];

    int time = 0, done = 0;
    queue[tail++] = 0;
    added[0] = 1;

    printf("Gantt Chart:\n");

    while (done < N)
    {
        int p = queue[head++];
        int run = remaining[p] < quantum ? remaining[p] : quantum;
        int start = time;

        time += run;
        remaining[p] -= run;

        printf("%s(%d-%d) ", name[p], start, time);

        for (int i = 0; i < N; i++)
        {
            if (!added[i] && arrival[i] <= time)
            {
                queue[tail++] = i;
                added[i] = 1;
            }
        }

        if (remaining[p] > 0)
            queue[tail++] = p;
        else
        {
            finish[p] = time;
            done++;
        }
    }

    double totalWT = 0, totalTAT = 0;

    printf("\n\nProcess\tTAT\tWT\n");

    for (int i = 0; i < N; i++)
    {
        int tat = finish[i] - arrival[i];
        int wt = tat - burst[i];

        totalTAT += tat;
        totalWT += wt;

        printf("%s\t%d\t%d\n", name[i], tat, wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / N);
    printf("\nAverage WT = %.2f\n", totalWT / N);

    return 0;
}
