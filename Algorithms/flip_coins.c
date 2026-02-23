#include <stdio.h>
#include <stdlib.h>

int max (int a, int b) { return a > b ? a : b;}

int main() {
    
    int n, m;
    char grid[105][15];

    while (scanf("%d %d", &n, &m) == 2) 
    {
        for (int i = 0; i < n; i++)
            scanf("%s", grid[i]);

        int best = 0;

        // Enumerate column flips mask
        for (int mask = 0; mask < (1 << m); mask++)
        {
            int total = 0;

            for (int i = 0; i < n; i++)
            {
                int ones = 0;

                for (int j = 0; j < m; j++)
                {
                    int bit = grid[i][j] - '0';

                    // If this column flipped
                    if (mask&(1<<j)) bit ^= 1;
                    
                    if (bit == 1) ones++;
                }

                // We can flip this row to have ones = m - ones
                total += max(ones, m - ones);
            }

            if (total > best) best = total;
        }
        printf("%d\n", best);

    }
    return 0;
}