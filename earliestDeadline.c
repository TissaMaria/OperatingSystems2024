#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int period;
    int execution_time;
    int remaining_time;
    int deadline;
    int next_deadline;
} Task;

void earliestDeadline(Task tasks[], int n, int totalTime) {
    printf("EDF\n");
    Task *current_task = NULL;
    int time = 0;

    while (time < totalTime) {
        // Update tasks at the beginning of each period
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = time + tasks[i].deadline;
            }
        }

        // Find the task with the earliest deadline
        Task *earliest_task = NULL;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (earliest_task == NULL || tasks[i].next_deadline < earliest_task->next_deadline) {
                    earliest_task = &tasks[i];
                }
            }
        }

        // Execute the task with the earliest deadline
        if (earliest_task != NULL) {
            earliest_task->remaining_time--;
            printf("Time %d: Executing task %d\n", time, earliest_task->id);
        } else {
            printf("Time %d: Idle\n", time);
        }

        // Increment time
        time++;
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n, totalTime;

    printf("Enter the number of tasks (max %d): ", MAX_TASKS);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter details for task %d\n", i + 1);
        tasks[i].id = i + 1;
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Deadline: ");
        scanf("%d", &tasks[i].deadline);
        tasks[i].remaining_time = 0;
        tasks[i].next_deadline = 0;
    }

    printf("Enter the total simulation time: ");
    scanf("%d", &totalTime);

    earliestDeadline(tasks, n, totalTime);

    return 0;
}
