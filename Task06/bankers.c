#include <stdio.h>

#define P 5
#define R 3

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maximum[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int available[R] = {3, 3, 2};

int need[P][R];

void calculateNeed()
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

int safeState(int work[R], int sequence[P])
{
    int finish[P] = {0};
    int count = 0;

    while (count < P)
    {
        int found = 0;

        for (int i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                int j;

                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            return 0;
    }

    return 1;
}

void printSequence(int sequence[P])
{
    for (int i = 0; i < P; i++)
        printf("P%d ", sequence[i]);
    printf("\n");
}

void requestResources(int process, int request[R])
{
    int work[R], sequence[P];

    for (int j = 0; j < R; j++)
    {
        if (request[j] > need[process][j])
        {
            printf("P%d request: Denied (exceeds need)\n", process);
            return;
        }

        if (request[j] > available[j])
        {
            printf("P%d request: Must wait (resources unavailable)\n",
                   process);
            return;
        }
    }

    for (int j = 0; j < R; j++)
    {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
        work[j] = available[j];
    }

    if (safeState(work, sequence))
    {
        printf("P%d request: Granted, safe sequence: ", process);
        printSequence(sequence);
    }
    else
    {
        for (int j = 0; j < R; j++)
        {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }

        printf("P%d request: Denied (unsafe state)\n", process);
    }
}

int main()
{
    int work[R], sequence[P];

    calculateNeed();

    for (int j = 0; j < R; j++)
        work[j] = available[j];

    printf("Initial System State\n");

    if (safeState(work, sequence))
    {
        printf("System is SAFE\n");
        printf("Safe sequence: ");
        printSequence(sequence);
    }

    int request1[R] = {1, 0, 2};
    int request4[R] = {3, 3, 0};
    int request0[R] = {0, 2, 0};

    printf("\nResource Requests:\n");

    requestResources(1, request1);
    requestResources(4, request4);
    requestResources(0, request0);

    return 0;
}
