#include<stdio.h>
void RoundRobin(int processes[],int n,int burst_time[],int arrival_time[],int timeQuantum){
    int remaining_time[n];
    int waiting_time[n];
    int turnaround_time[n];
    int completion_time[n];
    int current_time=0;
    for(int i=0;i<n;i++){
        remaining_time[i]=burst_time[i];
        waiting_time[i]=0;
    }
    while(1){
        int allDone=1;
        for(int i=0;i<n;i++){
            if(remaining_time[i]>0){
                allDone=0;
                if(remaining_time[i]<=timeQuantum){
                    current_time+=remaining_time[i];
                    turnaround_time[i]=current_time-arrival_time[i];
                    completion_time[i]=current_time;
                    remaining_time[i]=0;
                }else{
                    current_time+=timeQuantum;
                    remaining_time[i]-=timeQuantum;
                }
            }
        }
        if(allDone){
            break;
        }
    }
        for(int i=0;i<n;i++){
            waiting_time[i]=turnaround_time[i]-burst_time[i];
        }
        printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
        for(int i=0;i<n;i++){
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i],arrival_time[i],burst_time[i],completion_time[i],waiting_time[i],turnaround_time[i]);

        }
    
}
int main(){
    int n;
    printf("Enter number of processes:");
    scanf("%d",&n);
    int timeQuantum;
    printf("Enter Time Quantum");
    scanf("%d",&timeQuantum);
    int processes[n],burst_time[n],arrival_time[n],priority[n];
    printf("Enter arrival time, burst time for each process\n");
    for(int i=0;i<n;i++){
        printf("Process %d ",i+1);
        scanf("%d%d",&arrival_time[i],&burst_time[i]);
        processes[i]=i+1;

    }
    RoundRobin(processes,n,burst_time,arrival_time,timeQuantum);
    return 0;
}