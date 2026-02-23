#include <stdio.h>

#define MAXN 100005

int maxHeap[MAXN], maxSize = 0;
int minHeap[MAXN], minSize = 0;

// ----- Max Heap -----
void maxPush(int x) {
    int i = ++maxSize;

    while (i > 1 && maxHeap[i/2] < x) {
        maxHeap[i] = maxHeap[i/2];
        i /= 2;
    }
    maxHeap[i] = x;
}

int maxPop() {
    int ret = maxHeap[1];
    int x = maxHeap[maxSize--];
    int i = 1, child;

    while (i*2 <= maxSize) {
        child = i*2;
        if (child+1 <= maxSize && maxHeap[child+1] > maxHeap[child]) child++;
        if (maxHeap[child] <= x) break;
        maxHeap[i] = maxHeap[child];
        i = child;
    }
    maxHeap[i] = x;
    return ret;
}

// ----- Min Heap -----
void minPush(int x) {
    int i = ++minSize;

    while (i > 1 && minHeap[i/2] > x) {
        minHeap[i] = minHeap[i/2];
        i /= 2;
    }
    minHeap[i] = x;
}

int minPop() {
    int ret = minHeap[1];
    int x = minHeap[minSize--];
    int i = 1, child;

    while (i*2 <= minSize) {
        child = i*2;
        if (child+1 <= minSize && minHeap[child+1] < minHeap[child]) child++;
        if (minHeap[child] >= x) break;
        minHeap[i] = minHeap[child];
        i = child;
    }
    minHeap[i] = x;
    return ret;
}

int main() {
    int n, x;

    scanf("%d", &n);

    for (int i = 1; i <= n; i ++) {
        scanf("%d", &x);

        // Step 1: push to max heap
        maxPush(x);

        // Step 2: move largest to min heap
        minPush(maxPop());

        // Step 3: balance heap sizes
        if (minSize > maxSize) maxPush(minPop());

        // Step 4: print median
        if (i % 2 == 1) printf("%d\n", maxHeap[1]);
    }
    return 0;
}