#include <stdio.h>

struct Process {
    int pid; 
    int arrival_time;
    int burst_time; 
    int completion_time; 
    int turnaround_time; 
    int waiting_time; 
};

void findCompletionTime(struct Process proc[], int n) {
    int current_time = 0;
    int completed = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    
    while (completed != n) {
        int min_index = -1;
        int min_burst = 1000000;
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (proc[i].burst_time < min_burst) {
                    min_burst = proc[i].burst_time;
                    min_index = i;
                }
            }
        }
        
        if (min_index == -1) {
            current_time++;
        } else {
            proc[min_index].completion_time = current_time + proc[min_index].burst_time;
            current_time += proc[min_index].burst_time;
            proc[min_index].turnaround_time = proc[min_index].completion_time - proc[min_index].arrival_time;
            proc[min_index].waiting_time = proc[min_index].turnaround_time - proc[min_index].burst_time;
            is_completed[min_index] = 1;
            completed++;
        }
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time, 
               proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }
    
    findCompletionTime(proc, n);
    
    printProcesses(proc, n);
    
    return 0;
}
