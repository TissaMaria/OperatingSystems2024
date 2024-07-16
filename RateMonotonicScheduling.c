#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int period;
    int execution_time;
    int remaining_time;
} Task;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculateLCM(Task tasks[], int n) {
    int result = tasks[0].period;
    for (int i = 1; i < n; i++) {
        result = lcm(result, tasks[i].period);
    }
    return result;
}

void rateMonotonic(Task tasks[], int n, int simulationTime) {
    printf("RMS\n");
    int time = 0;
    while (time < simulationTime) {
        int min_period = 9999;
        int index = -1;

        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
            }
            if (tasks[i].remaining_time > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                index = i;
            }
        }

        if (index != -1) {
            printf("Time %d : Task %d\n", time, tasks[index].id);
            tasks[index].remaining_time--;
        } else {
            printf("Time %d : Idle\n", time);
        }
        time++;
    }
    printf("\n");
}

int main() {
    Task tasks[MAX_TASKS];
    int n;

    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    if (n > MAX_TASKS) {
        printf("Error: Number of tasks exceeds the maximum allowed (%d).\n", MAX_TASKS);
        return 1;
    }

    double utilization = 0.0;
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter period and execution time for task %d: ", i + 1);
        scanf("%d %d", &tasks[i].period, &tasks[i].execution_time);
        tasks[i].remaining_time = 0;
        utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    if (utilization > 1.0) {
        printf("Error: The set of tasks is not schedulable under RMS (Utilization > 100%%).\n");
        return 1;
    }

    int simulation_time = calculateLCM(tasks, n);
    printf("Simulation Time (LCM of Periods): %d\n", simulation_time);

    rateMonotonic(tasks, n, simulation_time);

    return 0;
}
