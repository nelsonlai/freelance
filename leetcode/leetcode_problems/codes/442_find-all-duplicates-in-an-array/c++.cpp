/*
 * Problem: Find All Duplicates in an Array
 * Difficulty: Medium
 * Tags: array, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        for (int num : nums) {
            int index = abs(num) - 1;
            if (nums[index] < 0) {
                result.push_back(abs(num));
            } else {
                nums[index] = -nums[index];
            }
        }
        return result;
    }
};