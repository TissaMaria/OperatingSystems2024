#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    printf("\nFCFS Disk Scheduling:\n");
    printf("Head Movement: %d", head);
    
    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
}

void scan(int requests[], int n, int head, int disk_size) {
    int total_movement = 0, direction = 1; // direction: 1 for up, -1 for down
    printf("\nSCAN Disk Scheduling:\n");

    // Sorting the request array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Head Movement: %d", head);
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            start = i;
            break;
        }
    }

    if (direction == 1) { // move towards the higher end
        for (int i = start; i < n; i++) {
            total_movement += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
        total_movement += abs(disk_size - head - 1);
        head = disk_size - 1;
        printf(" -> %d", head);
        for (int i = start - 1; i >= 0; i--) {
            total_movement += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
    } else { // move towards the lower end
        for (int i = start - 1; i >= 0; i--) {
            total_movement += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
        total_movement += abs(head);
        head = 0;
        printf(" -> %d", head);
        for (int i = start; i < n; i++) {
            total_movement += abs(requests[i] - head);
            head = requests[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
}

void c_scan(int requests[], int n, int head, int disk_size) {
    int total_movement = 0;
    printf("\nC-SCAN Disk Scheduling:\n");

    // Sorting the request array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Head Movement: %d", head);
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            start = i;
            break;
        }
    }

    for (int i = start; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    total_movement += abs(disk_size - head - 1);
    head = 0;
    printf(" -> %d", head);
    total_movement += disk_size - 1;
    for (int i = 0; i < start; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement: %d\n", total_movement);
}

int main() {
    int requests[MAX], n, head, disk_size;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    fcfs(requests, n, head);
    scan(requests, n, head, disk_size);
    c_scan(requests, n, head, disk_size);

    return 0;
}
