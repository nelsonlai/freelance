/*
 * Problem: Teemo Attacking
 * Difficulty: Easy
 * Tags: array, sort
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
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty()) {
            return 0;
        }
        
        int total = 0;
        for (int i = 0; i < timeSeries.size() - 1; i++) {
            total += min(duration, timeSeries[i+1] - timeSeries[i]);
        }
        
        return total + duration;
    }
};