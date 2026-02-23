#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int h; // hight
    int cnt;  // how many subarrayse ending here have min = h
} Node;

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    if (scanf("%d", &n) != 1) return 0;

    char *row = (char *) malloc( (n + 5) * sizeof(char)); // memory allocate from heap
    int *height = (int *) malloc (n * sizeof(int));
    Node *st = (Node *) malloc (n * sizeof(Node));  // stack for monotonic stack

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter the row %d: ", i + 1);
        scanf("%s", row);

        // update histogram heights of consecutive zeros
        for (int j = 0; j < n; j++) {
            if (row[j] == '0') height[j] += 1;
            else height[j] = 0;
        }

        // monotonic stack to compute sum of subarray minimums
        int top = 0;  // stack size
        long long cur = 0;  // sum of mins for subarrays ending at current j

        for (int j = 0; j < n; j++) {
            int h = height[j];
            int cnt = 1;

            while (top > 0 && st[top - 1].h >= h) {
                cnt += st[top - 1].cnt;
                cur -= (long long) st[top - 1].h * st[top - 1].cnt;
                top --;
            }

            st[top].h = h;
            st[top].cnt = cnt;
            top ++;

            cur += (long long) h * cnt;
            ans += cur;
        }
    }

    printf("Subarray acount: %lld\n", ans);

    free(row);
    free(height);
    free(st);

    return 0;
}

