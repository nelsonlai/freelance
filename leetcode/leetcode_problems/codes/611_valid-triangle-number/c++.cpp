/*
 * Problem: Valid Triangle Number
 * Difficulty: Medium
 * Tags: array, greedy, sort, search
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
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int count = 0;
        
        for (int i = 0; i < nums.size() - 2; i++) {
            int k = i + 2;
            for (int j = i + 1; j < nums.size() - 1; j++) {
                while (k < nums.size() && nums[i] + nums[j] > nums[k]) {
                    k++;
                }
                count += k - j - 1;
            }
        }
        
        return count;
    }
};