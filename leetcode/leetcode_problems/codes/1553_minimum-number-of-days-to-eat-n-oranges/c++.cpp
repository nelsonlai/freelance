/*
 * Problem: Minimum Number of Days to Eat N Oranges
 * Difficulty: Hard
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> memo;
    
    int minDaysHelper(int n) {
        if (n <= 1) {
            return n;
        }
        
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
        
        int result = n;
        result = min(result, 1 + minDaysHelper(n - 1));
        
        if (n % 2 == 0) {
            result = min(result, 1 + minDaysHelper(n / 2));
        }
        
        if (n % 3 == 0) {
            result = min(result, 1 + minDaysHelper(n / 3));
        }
        
        memo[n] = result;
        return result;
    }
    
public:
    int minDays(int n) {
        memo.clear();
        return minDaysHelper(n);
    }
};