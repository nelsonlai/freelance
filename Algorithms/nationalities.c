#include <stdio.h>
#include <stdlib.h>

#define MAXK 300005
#define MAXX 100005
#define WINDOW 86400

typedef struct {
    int time;
    int nationality;
} Passenger;

Passenger queue[MAXK];
int head = 0, tail = 0;

int freq[MAXX] = {0};
int distinct = 0;


int main() {
    int n;
    scanf("%d", &n);

    int t, k, x;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &t, &k);
        current_time = t;

        for (int j = 0; j < k; j++) {
            scanf("%d", &x);

            queue[tail].time = t;
            queue[tail].nationality = x;
            tail ++;

            if (freq[x] == 0) {
                distinct ++;
            }
            freq[x] ++;
        }

        while (head < tail && queue[head].time <= current_time - WINDOW) {
            int nat = queue[head].nationality;
            freq[nat] --;
            if (freq[nat] == 0) {
                distinct --;
            }
            head ++;
        }
        printf("%d\n", distinct);
    }
    return 0;
}