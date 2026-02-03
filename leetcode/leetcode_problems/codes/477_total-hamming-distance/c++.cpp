/*
 * Problem: Total Hamming Distance
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int total = 0;
        int n = nums.size();
        
        for (int i = 0; i < 32; i++) {
            int countOnes = 0;
            for (int num : nums) {
                countOnes += (num >> i) & 1;
            }
            total += countOnes * (n - countOnes);
        }
        
        return total;
    }
};