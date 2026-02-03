/*
 * Problem: Single Number III
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xor_val = 0;
        for (int num : nums) {
            xor_val ^= num;
        }
        
        int diff = xor_val & (-xor_val);
        
        int x = 0;
        for (int num : nums) {
            if (num & diff) {
                x ^= num;
            }
        }
        
        return {x, xor_val ^ x};
    }
};