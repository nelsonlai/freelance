/*
 * Problem: Array Nesting
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        vector<bool> visited(nums.size(), false);
        int maxLength = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
                int count = 0;
                int j = i;
                while (!visited[j]) {
                    visited[j] = true;
                    j = nums[j];
                    count++;
                }
                maxLength = max(maxLength, count);
            }
        }
        
        return maxLength;
    }
};