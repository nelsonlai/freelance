/*
 * Problem: Maximum Compatibility Score Sum
 * Difficulty: Medium
 * Tags: array, dp, bitmask, Hungarian algorithm
 * 
 * Approach: DP with bitmask - assign students to mentors optimally
 * Time Complexity: O(n * 2^n) where n is students
 * Space Complexity: O(2^n)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    int calculateScore(vector<int>& student, vector<int>& mentor) {
        int score = 0;
        for (int i = 0; i < student.size(); i++) {
            if (student[i] == mentor[i]) {
                score++;
            }
        }
        return score;
    }
    
    int dp(int mask, int mentorIdx, int n, vector<vector<int>>& score, vector<int>& memo) {
        if (mentorIdx == n) {
            return 0;
        }
        
        if (memo[mask] != -1) {
            return memo[mask];
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) {
                result = max(result, score[i][mentorIdx] + 
                    dp(mask | (1 << i), mentorIdx + 1, n, score, memo));
            }
        }
        
        return memo[mask] = result;
    }
    
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int n = students.size();
        vector<vector<int>> score(n, vector<int>(n));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                score[i][j] = calculateScore(students[i], mentors[j]);
            }
        }
        
        vector<int> memo(1 << n, -1);
        return dp(0, 0, n, score, memo);
    }
};