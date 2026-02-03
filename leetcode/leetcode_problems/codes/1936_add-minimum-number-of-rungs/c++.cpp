/*
 * Problem: Add Minimum Number of Rungs
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Calculate gaps between rungs, add rungs if gap > dist
 * Time Complexity: O(n) where n is rungs
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    int addRungs(vector<int>& rungs, int dist) {
        int count = 0;
        int prev = 0;
        
        for (int rung : rungs) {
            int gap = rung - prev;
            if (gap > dist) {
                count += (gap - 1) / dist;
            }
            prev = rung;
        }
        
        return count;
    }
};