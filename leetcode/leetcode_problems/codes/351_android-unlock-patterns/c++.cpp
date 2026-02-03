/*
 * Problem: Android Unlock Patterns
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    int count = 0;
    unordered_map<string, int> skip;
    
    void dfs(unordered_set<int>& visited, int last, int length, int m, int n) {
        if (length >= m) {
            count++;
        }
        if (length == n) {
            return;
        }
        
        for (int i = 1; i <= 9; i++) {
            if (visited.find(i) != visited.end()) {
                continue;
            }
            
            string edge = to_string(last) + "," + to_string(i);
            if (skip.find(edge) != skip.end() && 
                visited.find(skip[edge]) == visited.end()) {
                continue;
            }
            
            visited.insert(i);
            dfs(visited, i, length + 1, m, n);
            visited.erase(i);
        }
    }

public:
    int numberOfPatterns(int m, int n) {
        skip["1,3"] = 2; skip["3,1"] = 2;
        skip["1,7"] = 4; skip["7,1"] = 4;
        skip["3,9"] = 6; skip["9,3"] = 6;
        skip["7,9"] = 8; skip["9,7"] = 8;
        skip["1,9"] = 5; skip["9,1"] = 5;
        skip["2,8"] = 5; skip["8,2"] = 5;
        skip["3,7"] = 5; skip["7,3"] = 5;
        skip["4,6"] = 5; skip["6,4"] = 5;
        
        for (int i = 1; i <= 9; i++) {
            unordered_set<int> visited;
            visited.insert(i);
            dfs(visited, i, 1, m, n);
        }
        
        return count;
    }
};