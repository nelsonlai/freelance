/*
 * Problem: Find Two Non-overlapping Sub-arrays Each With Target Sum
 * Difficulty: Medium
 * Tags: array, dp, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        unordered_map<int, int> prefix;
        prefix[0] = -1;
        vector<int> best(n, INT_MAX);
        int bestSoFar = INT_MAX;
        int result = INT_MAX;
        int currentSum = 0;
        
        for (int i = 0; i < n; i++) {
            currentSum += arr[i];
            if (prefix.find(currentSum - target) != prefix.end()) {
                int start = prefix[currentSum - target];
                int length = i - start;
                if (start >= 0) {
                    result = min(result, best[start] + length);
                }
                bestSoFar = min(bestSoFar, length);
            }
            
            best[i] = bestSoFar;
            prefix[currentSum] = i;
        }
        
        return result == INT_MAX ? -1 : result;
    }
};