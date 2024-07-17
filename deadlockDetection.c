#include <stdio.h> 
 
#define MAX_PROCESSES 5 
#define MAX_RESOURCES 3 
 
int allocated[MAX_PROCESSES][MAX_RESOURCES]; 
int requested[MAX_PROCESSES][MAX_RESOURCES]; 
int available[MAX_RESOURCES]; 
int work[MAX_RESOURCES]; 
int finish[MAX_PROCESSES]; 
 
void initialize() 
{ 
    // Initialize allocated and requested matrices 
    for (int i = 0; i < MAX_PROCESSES; i++) 
    { 
        printf("Enter allocated resources for process P%d:\n", i); 
        for (int j = 0; j < MAX_RESOURCES; j++) 
            scanf("%d", &allocated[i][j]); 
 
        printf("Enter requested resources for process P%d:\n", i); 
        for (int j = 0; j < MAX_RESOURCES; j++) 
            scanf("%d", &requested[i][j]); 
 
        finish[i] = 0; // Process is not finished yet 
 
 
    } 
} 
 
int checkSafety() 
{ 
    for (int i = 0; i < MAX_RESOURCES; i++) 
        work[i] = available[i]; 
 
    int count = 0; 
    while (count < MAX_PROCESSES) 
    { 
        int found = 0; 
        for (int i = 0; i < MAX_PROCESSES; i++) 
        { 
            if (!finish[i]) 
            { 
                int j; 
                for (j = 0; j < MAX_RESOURCES; j++) 
                { 
                    if (requested[i][j] > work[j]) 
                        break; 
                } 
                if (j == MAX_RESOURCES) 
                { 
                    for (int k = 0; k < MAX_RESOURCES; k++) 
                        work[k] += allocated[i][k]; 
                    finish[i] = 1; 
                    found = 1; 
                    count++; 
                } 
            } 
        } 
        if (!found) 
            break; 
    } 
 
    return count == MAX_PROCESSES; 
} 
 
int main() 
{ 
    initialize(); 
 
    // Assume available resources are initially zero 
    for (int i = 0; i < MAX_RESOURCES; i++) 
        available[i] = 0; 
 
    if (checkSafety()) 
        printf("System is in safe state.\n"); 
    else 
        printf("System is in unsafe state.\n"); 
 
    return 0; 
} 
