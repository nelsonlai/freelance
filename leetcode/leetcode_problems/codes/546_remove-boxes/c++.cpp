/*
 * Problem: Remove Boxes
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
    unordered_map<string, int> memo;
    
    int dp(int i, int j, int k, vector<int>& boxes) {
        if (i > j) {
            return 0;
        }
        
        string key = to_string(i) + "," + to_string(j) + "," + to_string(k);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        while (i < j && boxes[i] == boxes[i + 1]) {
            i++;
            k++;
        }
        
        int result = (k + 1) * (k + 1) + dp(i + 1, j, 0, boxes);
        
        for (int m = i + 1; m <= j; m++) {
            if (boxes[m] == boxes[i]) {
                result = max(result, dp(i + 1, m - 1, 0, boxes) + dp(m, j, k + 1, boxes));
            }
        }
        
        memo[key] = result;
        return result;
    }

public:
    int removeBoxes(vector<int>& boxes) {
        return dp(0, boxes.size() - 1, 0, boxes);
    }
};