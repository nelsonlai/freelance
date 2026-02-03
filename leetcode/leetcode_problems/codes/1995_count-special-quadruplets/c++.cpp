/*
 * Problem: Count Special Quadruplets
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use hash map to store nums[d] - nums[c], check for nums[a] + nums[b]
 * Time Complexity: O(n^2) where n is length
 * Space Complexity: O(n^2)
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        
        // nums[a] + nums[b] == nums[d] - nums[c]
        // Store nums[d] - nums[c] for all d > c
        unordered_map<int, int> diffCount;
        
        for (int c = n - 2; c > 0; c--) {
            for (int d = c + 1; d < n; d++) {
                int diff = nums[d] - nums[c];
                diffCount[diff]++;
            }
            
            for (int a = 0; a < c; a++) {
                for (int b = a + 1; b < c; b++) {
                    int target = nums[a] + nums[b];
                    count += diffCount[target];
                }
            }
        }
        
        return count;
    }
};