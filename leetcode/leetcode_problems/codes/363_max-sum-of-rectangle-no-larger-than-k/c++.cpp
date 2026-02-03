/*
 * Problem: Max Sum of Rectangle No Larger Than K
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        int result = INT_MIN;
        
        for (int left = 0; left < n; left++) {
            vector<int> rowSum(m, 0);
            for (int right = left; right < n; right++) {
                for (int i = 0; i < m; i++) {
                    rowSum[i] += matrix[i][right];
                }
                
                set<int> prefixSum;
                prefixSum.insert(0);
                int currSum = 0;
                
                for (int sum : rowSum) {
                    currSum += sum;
                    auto it = prefixSum.lower_bound(currSum - k);
                    if (it != prefixSum.end()) {
                        result = max(result, currSum - *it);
                    }
                    prefixSum.insert(currSum);
                }
            }
        }
        
        return result;
    }
};