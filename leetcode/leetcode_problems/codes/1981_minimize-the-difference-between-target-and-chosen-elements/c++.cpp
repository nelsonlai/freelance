/*
 * Problem: Minimize the Difference Between Target and Chosen Elements
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - track all possible sums, find closest to target
 * Time Complexity: O(n * m * sum_range) where n is rows, m is cols
 * Space Complexity: O(sum_range)
 */

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        unordered_set<int> possibleSums;
        possibleSums.insert(0);
        
        for (auto& row : mat) {
            unordered_set<int> newSums;
            int rowMin = *min_element(row.begin(), row.end());
            int rowMax = *max_element(row.begin(), row.end());
            
            for (int s : possibleSums) {
                for (int num : row) {
                    int newSum = s + num;
                    if (newSum <= target + rowMax) {
                        newSums.insert(newSum);
                    }
                }
            }
            possibleSums = newSums;
        }
        
        int minDiff = INT_MAX;
        for (int s : possibleSums) {
            minDiff = min(minDiff, abs(s - target));
        }
        
        return minDiff;
    }
};