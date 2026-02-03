/*
 * Problem: Wiggle Sort
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 0; i < nums.size() - 1; i++) {
            if ((i % 2 == 0 && nums[i] > nums[i + 1]) ||
                (i % 2 == 1 && nums[i] < nums[i + 1])) {
                swap(nums[i], nums[i + 1]);
            }
        }
    }
};