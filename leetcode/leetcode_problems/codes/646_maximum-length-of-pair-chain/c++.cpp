/*
 * Problem: Maximum Length of Pair Chain
 * Difficulty: Medium
 * Tags: array, dp, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int count = 0;
        int end = INT_MIN;
        
        for (auto& pair : pairs) {
            if (pair[0] > end) {
                count++;
                end = pair[1];
            }
        }
        
        return count;
    }
};