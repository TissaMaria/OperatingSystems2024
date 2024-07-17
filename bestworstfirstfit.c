#include <stdio.h>
#include <stdlib.h>

#define MAX 25

int frag[MAX], b[MAX], f[MAX], nf, nb;
int bf[MAX], ff[MAX];

void firstfit() {
    int i, j;

    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] == 0 && b[j] >= f[i]) {
                ff[i] = j;
                frag[i] = b[j] - f[i];
                bf[j] = 1;
                break;
            }
        }
    }

    printf("\nFile Size:\tBlock Size:");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t", f[i], b[ff[i]]);
        else
            printf("\n%d\t\tNot Allocated", f[i]);
    }
    printf("\n");
}

void bestfit() {
    int i, j, bestIdx;

    for (i = 1; i <= nf; i++) {
        bestIdx = -1;
        for (j = 1; j <= nb; j++) {
            if (bf[j] == 0 && b[j] >= f[i]) {
                if (bestIdx == -1 || b[j] < b[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            ff[i] = bestIdx;
            frag[i] = b[bestIdx] - f[i];
            bf[bestIdx] = 1;
        }
    }

    printf("\nFile Size:\tBlock Size:");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t", f[i], b[ff[i]]);
        else
            printf("\n%d\t\tNot Allocated", f[i]);
    }
    printf("\n");
}

void worstfit() {
    int i, j, worstIdx;

    for (i = 1; i <= nf; i++) {
        worstIdx = -1;
        for (j = 1; j <= nb; j++) {
            if (bf[j] == 0 && b[j] >= f[i]) {
                if (worstIdx == -1 || b[j] > b[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            ff[i] = worstIdx;
            frag[i] = b[worstIdx] - f[i];
            bf[worstIdx] = 1;
        }
    }

    printf("\nFile Size:\tBlock Size:");
    for (i = 1; i <= nf; i++) {
        if (ff[i] != 0)
            printf("\n%d\t\t%d\t\t", f[i], b[ff[i]]);
        else
            printf("\n%d\t\tNot Allocated", f[i]);
    }
    printf("\n");
}

int main() {
    int c;

    printf("Enter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("Enter the size of the blocks:\n");
    for (int i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
        bf[i] = 0; // initialize
    }

    printf("Enter the size of the files:\n");
    for (int i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
    }

    while (1) {
        printf("\n1. First Fit 2. Best Fit 3. Worst Fit 4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                firstfit();
                break;
            case 2:
                bestfit();
                break;
            case 3:
                worstfit();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }

        // Reset for next
        for (int i = 1; i <= nb; i++) bf[i] = 0;
        for (int i = 1; i <= nf; i++) ff[i] = 0;
    }
    return 0;
}
