/*
 * Problem: Sum of All Subset XOR Totals
 * Difficulty: Easy
 * Tags: array, math, bit manipulation
 * 
 * Approach: For each bit position, count subsets where bit is set
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int result = 0;
        int n = nums.size();
        
        for (int bit = 0; bit < 32; bit++) {
            int count = 0;
            for (int num : nums) {
                if (num & (1 << bit)) {
                    count++;
                }
            }
            
            if (count > 0) {
                result += (1 << bit) * (1 << (n - 1));
            }
        }
        
        return result;
    }
};