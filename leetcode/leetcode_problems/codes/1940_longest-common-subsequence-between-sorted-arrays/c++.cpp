/*
 * Problem: Longest Common Subsequence Between Sorted Arrays
 * Difficulty: Medium
 * Tags: array, hash, sort, two pointers
 * 
 * Approach: Count frequency, return elements appearing in all arrays
 * Time Complexity: O(n * m) where n is arrays, m is avg length
 * Space Complexity: O(m)
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> longestCommonSubsequence(vector<vector<int>>& arrays) {
        unordered_map<int, int> count;
        for (auto& arr : arrays) {
            unordered_set<int> seen;
            for (int num : arr) {
                if (seen.insert(num).second) {
                    count[num]++;
                }
            }
        }
        
        int n = arrays.size();
        vector<int> result;
        for (auto& [num, cnt] : count) {
            if (cnt == n) {
                result.push_back(num);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};