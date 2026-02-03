/*
 * Problem: Scramble String
 * Difficulty: Hard
 * Tags: string, tree, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    unordered_map<string, bool> memo;
    
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) {
            return true;
        }
        if (s1.length() != s2.length()) {
            return false;
        }
        
        string key = s1 + "#" + s2;
        if (memo.count(key)) {
            return memo[key];
        }
        
        string sorted1 = s1;
        string sorted2 = s2;
        sort(sorted1.begin(), sorted1.end());
        sort(sorted2.begin(), sorted2.end());
        if (sorted1 != sorted2) {
            memo[key] = false;
            return false;
        }
        
        int n = s1.length();
        for (int i = 1; i < n; i++) {
            if ((isScramble(s1.substr(0, i), s2.substr(0, i)) && 
                 isScramble(s1.substr(i), s2.substr(i))) ||
                (isScramble(s1.substr(0, i), s2.substr(n - i)) && 
                 isScramble(s1.substr(i), s2.substr(0, n - i)))) {
                memo[key] = true;
                return true;
            }
        }
        
        memo[key] = false;
        return false;
    }
};