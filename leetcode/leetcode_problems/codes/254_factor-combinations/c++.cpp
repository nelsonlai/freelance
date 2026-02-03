/*
 * Problem: Factor Combinations
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
private:
    void backtrack(int start, int target, vector<int>& path, vector<vector<int>>& result) {
        if (target == 1 && path.size() > 1) {
            result.push_back(path);
            return;
        }
        
        for (int i = start; i * i <= target; i++) {
            if (target % i == 0) {
                path.push_back(i);
                backtrack(i, target / i, path, result);
                path.pop_back();
            }
        }
        
        if (target >= start) {
            path.push_back(target);
            backtrack(target, 1, path, result);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> result;
        vector<int> path;
        backtrack(2, n, path, result);
        return result;
    }
};