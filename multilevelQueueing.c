#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int pid;
    char type[10];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Processes;

void sortProcessByArrivalTime(Processes *queue, int count) {
    for (int i = 0; i <= count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (queue[j].arrival_time > queue[j + 1].arrival_time) {
                Processes temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
}

void calculateTime(Processes *queue, int count, int *currentTime) {
    for (int i = 0; i < count; i++) {
        if (*currentTime < queue[i].arrival_time) {
            *currentTime = queue[i].arrival_time;
        }
        queue[i].completion_time = *currentTime + queue[i].burst_time;
        queue[i].turnaround_time = queue[i].completion_time - queue[i].arrival_time;
        queue[i].waiting_time = queue[i].turnaround_time - queue[i].burst_time;
        *currentTime = queue[i].completion_time;
    }
}

void simulateMultiLevelQueueing(Processes *process, int n) {
    Processes systemQueue[MAX], userQueue[MAX];
    int systemCount = 0, userCount = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(process[i].type, "system") == 0) {
            systemQueue[systemCount++] = process[i];
        } else if (strcmp(process[i].type, "user") == 0) {
            userQueue[userCount++] = process[i];
        }
    }

    sortProcessByArrivalTime(systemQueue, systemCount);
    sortProcessByArrivalTime(userQueue, userCount);

    int currentTime = 0;
    calculateTime(systemQueue, systemCount, &currentTime);
    calculateTime(userQueue, userCount, &currentTime);

    printf("PID\tType\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;

    for (int i = 0; i < systemCount; i++) {
        totalTurnaroundTime += systemQueue[i].turnaround_time;
        totalWaitingTime += systemQueue[i].waiting_time;
        printf("%d\t%s\t%d\t%d\t\t%d\t\t%d\t\t\t%d\n", systemQueue[i].pid, systemQueue[i].type, systemQueue[i].arrival_time, systemQueue[i].burst_time, systemQueue[i].completion_time, systemQueue[i].turnaround_time, systemQueue[i].waiting_time);
    }

    for (int i = 0; i < userCount; i++) {
        totalTurnaroundTime += userQueue[i].turnaround_time;
        totalWaitingTime += userQueue[i].waiting_time;
        printf("%d\t%s\t%d\t%d\t\t%d\t\t%d\t\t\t%d\n", userQueue[i].pid, userQueue[i].type, userQueue[i].arrival_time, userQueue[i].burst_time, userQueue[i].completion_time, userQueue[i].turnaround_time, userQueue[i].waiting_time);
    }

    int totalProcesses = systemCount + userCount;
    printf("Average Turnaround Time: %f\n", totalTurnaroundTime / totalProcesses);
    printf("Average Waiting Time: %f\n", totalWaitingTime / totalProcesses);
}

int main() {
    Processes process[MAX];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Process ID: ");
        scanf("%d", &process[i].pid);
        printf("Process Type (system/user): ");
        scanf("%s", process[i].type);
        printf("Process Arrival Time: ");
        scanf("%d", &process[i].arrival_time);
        printf("Process Burst Time: ");
        scanf("%d", &process[i].burst_time);
    }

    simulateMultiLevelQueueing(process, n);
    return 0;
}
