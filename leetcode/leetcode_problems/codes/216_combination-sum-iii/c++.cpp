/*
 * Problem: Combination Sum III
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
private:
    void backtrack(int start, int k, int remaining, vector<int>& path, vector<vector<int>>& result) {
        if (path.size() == k && remaining == 0) {
            result.push_back(path);
            return;
        }
        
        if (path.size() >= k || remaining < 0) {
            return;
        }
        
        for (int i = start; i <= 9; i++) {
            path.push_back(i);
            backtrack(i + 1, k, remaining - i, path, result);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> path;
        backtrack(1, k, n, path, result);
        return result;
    }
};