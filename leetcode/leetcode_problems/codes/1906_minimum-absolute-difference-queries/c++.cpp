/*
 * Problem: Minimum Absolute Difference Queries
 * Difficulty: Medium
 * Tags: array, hash, prefix sum
 * 
 * Approach: For each query, find all distinct numbers in range, compute min diff
 * Time Complexity: O(n * 100 + q * 100) where q is queries, numbers are 1-100
 * Space Complexity: O(n * 100)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> prefix(n + 1, vector<int>(101, 0));
        
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i];
            prefix[i + 1][nums[i]]++;
        }
        
        vector<int> result;
        for (auto& query : queries) {
            int l = query[0];
            int r = query[1];
            
            vector<int> distinct;
            for (int i = 1; i <= 100; i++) {
                if (prefix[r + 1][i] - prefix[l][i] > 0) {
                    distinct.push_back(i);
                }
            }
            
            if (distinct.size() < 2) {
                result.push_back(-1);
            } else {
                int minDiff = INT_MAX;
                for (int i = 0; i < distinct.size() - 1; i++) {
                    minDiff = min(minDiff, distinct[i + 1] - distinct[i]);
                }
                result.push_back(minDiff);
            }
        }
        
        return result;
    }
};