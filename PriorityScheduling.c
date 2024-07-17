#include <stdio.h>
#include <limits.h>
#define MAX(a,b) ((a)>(b)?(a):(b))

void priorityNonPreemptive(int processes[], int n, int burst_time[], int priority[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n], is_completed[n];
    int current_time = 0, completed = 0;

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed != n) {
        int selected_process = -1;
        int highest_priority = INT_MAX;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && is_completed[i] == 0) {
                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    selected_process = i;
                }
            }
        }

        if (selected_process != -1) {
            current_time += burst_time[selected_process];
            completion_time[selected_process] = current_time;
            turnaround_time[selected_process] = completion_time[selected_process] - arrival_time[selected_process];
            waiting_time[selected_process] = turnaround_time[selected_process] - burst_time[selected_process];
            is_completed[selected_process] = 1;
            completed++;
        } else {
            current_time++; // No process is ready yet, move to the next time unit
        }
    }

    printf("\nNon-Preemptive Priority Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }
}


void priorityPreemptive(int processes[], int n, int burst_time[], int priority[], int arrival_time[]) {
    int remaining_time[n], waiting_time[n], turnaround_time[n], completion_time[n];
    int completed = 0, current_time = 0;
    int is_completed[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        is_completed[i] = 0;
    }

    while (completed != n) {
        int selected_process = -1;
        int highest_priority = INT_MAX;

        // Find the process with the highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && is_completed[i] == 0) {
                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    selected_process = i;
                }
            }
        }

        if (selected_process != -1) {
            remaining_time[selected_process]--;
            current_time++;

            if (remaining_time[selected_process] == 0) {
                completion_time[selected_process] = current_time;
                turnaround_time[selected_process] = completion_time[selected_process] - arrival_time[selected_process];
                waiting_time[selected_process] = turnaround_time[selected_process] - burst_time[selected_process];
                is_completed[selected_process] = 1;
                completed++;
            }
        } else {
            current_time++; // No process is ready yet, move to the next time unit
        }
    }

    printf("\nPreemptive Priority Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }
}


int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n], arrival_time[n], priority[n];
    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d%d", &arrival_time[i], &burst_time[i], &priority[i]);
        processes[i] = i + 1;
    }
    priorityNonPreemptive(processes, n, burst_time, priority, arrival_time);
    priorityPreemptive(processes, n, burst_time, priority, arrival_time);
    return 0;
}
