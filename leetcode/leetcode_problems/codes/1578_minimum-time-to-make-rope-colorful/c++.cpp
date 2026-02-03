/*
 * Problem: Minimum Time to Make Rope Colorful
 * Difficulty: Medium
 * Tags: array, string, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int result = 0;
        int i = 0;
        int n = colors.length();
        
        while (i < n) {
            int j = i;
            int total = 0;
            int maxTime = 0;
            
            while (j < n && colors[j] == colors[i]) {
                total += neededTime[j];
                maxTime = max(maxTime, neededTime[j]);
                j++;
            }
            
            if (j > i + 1) {
                result += total - maxTime;
            }
            
            i = j;
        }
        
        return result;
    }
};