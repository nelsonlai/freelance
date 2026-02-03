/*
 * Problem: Split Array with Equal Sum
 * Difficulty: Hard
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        if (n < 7) {
            return false;
        }
        
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        
        for (int j = 3; j < n - 3; j++) {
            unordered_set<int> seen;
            for (int i = 1; i < j - 1; i++) {
                if (prefixSum[i] == prefixSum[j] - prefixSum[i + 1]) {
                    seen.insert(prefixSum[i]);
                }
            }
            
            for (int k = j + 2; k < n - 1; k++) {
                if (prefixSum[n] - prefixSum[k + 1] == prefixSum[k] - prefixSum[j + 1]) {
                    if (seen.find(prefixSum[n] - prefixSum[k + 1]) != seen.end()) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
};