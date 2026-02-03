/*
 * Problem: Minimum Swaps to Arrange a Binary Grid
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> trailingZeros;
        
        for (auto& row : grid) {
            int count = 0;
            for (int i = n - 1; i >= 0; i--) {
                if (row[i] == 0) {
                    count++;
                } else {
                    break;
                }
            }
            trailingZeros.push_back(count);
        }
        
        int swaps = 0;
        for (int i = 0; i < n; i++) {
            int required = n - 1 - i;
            if (trailingZeros[i] >= required) {
                continue;
            }
            
            bool found = false;
            for (int j = i + 1; j < n; j++) {
                if (trailingZeros[j] >= required) {
                    found = true;
                    swaps += j - i;
                    int temp = trailingZeros[j];
                    for (int k = j; k > i; k--) {
                        trailingZeros[k] = trailingZeros[k - 1];
                    }
                    trailingZeros[i] = temp;
                    break;
                }
            }
            
            if (!found) {
                return -1;
            }
        }
        
        return swaps;
    }
};