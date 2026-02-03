/*
 * Problem: Maximum Matrix Sum
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Can flip pairs of negatives, maximize sum by minimizing negatives
 * Time Complexity: O(n * m) where n, m are dimensions
 * Space Complexity: O(1)
 */

#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long total = 0;
        long long minAbs = LONG_MAX;
        int negativeCount = 0;
        
        for (auto& row : matrix) {
            for (int num : row) {
                total += abs(num);
                minAbs = min(minAbs, (long long)abs(num));
                if (num < 0) {
                    negativeCount++;
                }
            }
        }
        
        if (negativeCount % 2 == 1) {
            total -= 2 * minAbs;
        }
        
        return total;
    }
};