/*
 * Problem: Shortest Unsorted Continuous Subarray
 * Difficulty: Medium
 * Tags: array, greedy, sort, stack
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
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        
        int start = -1, end = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != sorted[i]) {
                if (start == -1) {
                    start = i;
                }
                end = i;
            }
        }
        
        return start == -1 ? 0 : end - start + 1;
    }
};