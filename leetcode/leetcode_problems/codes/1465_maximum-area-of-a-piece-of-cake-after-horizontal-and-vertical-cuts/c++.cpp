/*
 * Problem: Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        int MOD = 1000000007;
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        int maxH = max(horizontalCuts[0], h - horizontalCuts.back());
        for (int i = 1; i < horizontalCuts.size(); i++) {
            maxH = max(maxH, horizontalCuts[i] - horizontalCuts[i - 1]);
        }
        
        int maxW = max(verticalCuts[0], w - verticalCuts.back());
        for (int i = 1; i < verticalCuts.size(); i++) {
            maxW = max(maxW, verticalCuts[i] - verticalCuts[i - 1]);
        }
        
        return (long long)maxH * maxW % MOD;
    }
};