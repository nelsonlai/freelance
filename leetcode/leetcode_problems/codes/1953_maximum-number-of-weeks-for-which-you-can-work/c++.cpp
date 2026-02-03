/*
 * Problem: Maximum Number of Weeks for Which You Can Work
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: If max project <= sum of others + 1, can complete all; otherwise limited by max
 * Time Complexity: O(n) where n is milestones
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long total = accumulate(milestones.begin(), milestones.end(), 0LL);
        int maxMilestone = *max_element(milestones.begin(), milestones.end());
        long long rest = total - maxMilestone;
        
        if (maxMilestone <= rest + 1) {
            return total;
        } else {
            return 2 * rest + 1;
        }
    }
};