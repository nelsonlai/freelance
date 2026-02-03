/*
 * Problem: Sum of Distances
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; i++) {
            valueToIndices[nums[i]].push_back(i);
        }
        
        vector<long long> result(n, 0);
        
        for (auto& entry : valueToIndices) {
            vector<int>& indices = entry.second;
            if (indices.size() == 1) {
                continue;
            }
            
            vector<long long> prefix(indices.size() + 1, 0);
            for (int i = 0; i < indices.size(); i++) {
                prefix[i + 1] = prefix[i] + indices[i];
            }
            
            int m = indices.size();
            for (int i = 0; i < indices.size(); i++) {
                int idx = indices[i];
                long long leftSum = (long long)i * idx - prefix[i];
                long long rightSum = (prefix[m] - prefix[i + 1]) - (long long)(m - i - 1) * idx;
                result[idx] = leftSum + rightSum;
            }
        }
        
        return result;
    }
};