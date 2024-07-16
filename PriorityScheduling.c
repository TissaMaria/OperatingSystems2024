#include <stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
void priorityNonPreemptive(int processes[],int n, int burst_time[],int priority[],int arrival_time[]){
    int waiting_time[n], turnaround_time[n];
    waiting_time[0]=MAX(0,arrival_time[0]);
    for(int i=1;i<n;i++){
        waiting_time[i]=MAX(0,waiting_time[i-1]+burst_time[i-1]-arrival_time[i]);
        for(int i=0;i<n;i++){
            turnaround_time[i]=waiting_time[i]+burst_time[i];
        }
        printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
        for(int i=0;i<n;i++){
            printf("%d\t%d\t%d\t%d\t%d\n",processes[i],arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
        }
    }
    
}
void priorityPreemptive(int processes[],int n, int burst_time[],int priority[],int arrival_time[]){
    int remaining_time[n],waiting_time[n],turnaround_time[n],completed=0,current_time=0;
    for(int i=0;i<n;i++){
        remaining_time[i]=burst_time[i];
        waiting_time[i]=0;

    }
    while(completed!=n){
        int selected_process=-1;
        int highest_priority=-1;
        for(int i=0;i<n;i++){
            if(remaining_time[i]>0 && priority[i]>highest_priority && current_time>=arrival_time[i]){
                highest_priority=priority[i];
                selected_process=i;
            }
        }
        if(selected_process==-1){
            current_time++;
            continue;
        }
        remaining_time[selected_process]--;
        current_time++;
        if(remaining_time[selected_process]==0){
            completed++;
            turnaround_time[selected_process]=current_time-arrival_time[selected_process];

        }
    }
    for(int i=0;i<n;i++){
        waiting_time[i]=turnaround_time[i]-burst_time[i];
    }
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
        for(int i=0;i<n;i++){
            printf("%d\t%d\t%d\t%d\t%d\n",processes[i],arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
        }
    
}
int main(){
    int n;
    printf("Enter number of processes:");
    scanf("%d",&n);
    int processes[n],burst_time[n],arrival_time[n],priority[n];
    printf("Enter arrival time, burst time and priority for each process");
    for(int i=0;i<n;i++){
        printf("Process %d",i+1);
        scanf("%d%d%d",&arrival_time[i],&burst_time[i],&priority[i]);
        processes[i]=i+1;

    }
    printf("Non Preemptive");
    priorityNonPreemptive(processes,n,burst_time,priority,arrival_time);
    printf("Preemptive");
    priorityPreemptive(processes,n,burst_time,priority,arrival_time);
    return 0;
}