/*
 * Problem: Lexicographical Numbers
 * Difficulty: Medium
 * Tags: graph, sort, search
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
private:
    void dfs(int current, int n, vector<int>& result) {
        if (current > n) {
            return;
        }
        result.push_back(current);
        for (int i = 0; i < 10; i++) {
            int next = current * 10 + i;
            if (next > n) {
                return;
            }
            dfs(next, n, result);
        }
    }

public:
    vector<int> lexicalOrder(int n) {
        vector<int> result;
        for (int i = 1; i < 10; i++) {
            dfs(i, n, result);
        }
        return result;
    }
};