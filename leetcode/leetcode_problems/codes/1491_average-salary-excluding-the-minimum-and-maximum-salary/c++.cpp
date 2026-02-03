/*
 * Problem: Average Salary Excluding the Minimum and Maximum Salary
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    double average(vector<int>& salary) {
        int sum = 0;
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        
        for (int s : salary) {
            sum += s;
            minVal = min(minVal, s);
            maxVal = max(maxVal, s);
        }
        
        return (double)(sum - minVal - maxVal) / (salary.size() - 2);
    }
};