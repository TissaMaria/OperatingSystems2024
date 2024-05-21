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
    proc[0].completion_time = proc[0].arrival_time + proc[0].burst_time;
    proc[0].turnaround_time = proc[0].completion_time - proc[0].arrival_time;
    proc[0].waiting_time = proc[0].turnaround_time - proc[0].burst_time;
    for (int i = 1; i < n; i++) {
        if (proc[i].arrival_time > proc[i - 1].completion_time) {
            proc[i].completion_time = proc[i].arrival_time + proc[i].burst_time;
        } else {
            proc[i].completion_time = proc[i - 1].completion_time + proc[i].burst_time;
        }
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
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
