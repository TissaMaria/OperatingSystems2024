#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void fifo(int pages[], int n, int capacity) {
    int frames[MAX], page_faults = 0, next = 0;
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[next] = pages[i];
            next = (next + 1) % capacity;
            page_faults++;
        }

        printf("\nFrames: ");
        for (int j = 0; j < capacity; j++)
            printf("%d ", frames[j]);
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

void lru(int pages[], int n, int capacity) {
    int frames[MAX], page_faults = 0, time[MAX], counter = 0;
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0, lru_index = 0, min_time = counter;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter++;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    lru_index = j;
                    break;
                }
                if (time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }
            frames[lru_index] = pages[i];
            time[lru_index] = counter++;
            page_faults++;
        }

        printf("\nFrames: ");
        for (int j = 0; j < capacity; j++)
            printf("%d ", frames[j]);
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

void optimal(int pages[], int n, int capacity) {
    int frames[MAX], page_faults = 0;
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int pos = -1, farthest = i + 1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = 0;
            frames[pos] = pages[i];
            page_faults++;
        }

        printf("\nFrames: ");
        for (int j = 0; j < capacity; j++)
            printf("%d ", frames[j]);
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX], n, capacity = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("The number of pages should be greater than zero.\n");
        return 1;
    }

    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the capacity of frames: ");
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("The capacity of frames should be greater than zero.\n");
        return 1;
    }

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}
