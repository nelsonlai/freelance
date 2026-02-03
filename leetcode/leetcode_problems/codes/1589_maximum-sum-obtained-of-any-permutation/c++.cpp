/*
 * Problem: Maximum Sum Obtained of Any Permutation
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    static const int MOD = 1000000007;
    
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size();
        vector<int> freq(n + 1, 0);
        
        for (auto& req : requests) {
            freq[req[0]]++;
            freq[req[1] + 1]--;
        }
        
        for (int i = 1; i < n; i++) {
            freq[i] += freq[i - 1];
        }
        
        sort(freq.begin(), freq.begin() + n);
        sort(nums.begin(), nums.end());
        
        long long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + (long long)freq[i] * nums[i]) % MOD;
        }
        
        return (int) result;
    }
};