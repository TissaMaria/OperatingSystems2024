#include <stdio.h>
#include <stdbool.h>

#define P 5 // processes
#define R 3 // resources

int allocation[P][R] = {
    {0, 1, 0}, // P0
    {2, 0, 0}, 
    {3, 0, 2}, 
    {2, 1, 1}, 
    {0, 0, 2}  
};

int maximum[P][R] = {
    {7, 5, 3}, 
    {3, 2, 2}, 
    {9, 0, 2}, 
    {2, 2, 2}, 
    {4, 3, 3}  
};

int available[R] = {3, 3, 2};

bool isSafeSequence() {
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    bool finish[P] = {0};
    int safeSeq[P];
    int count = 0;

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (allocation[p][j] + work[j] < maximum[p][j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[p][k];
                    
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return true;
}

int main() {
    isSafeSequence();
    return 0;
}
