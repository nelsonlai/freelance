/*
 * Problem: String Compression II
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

class Solution {
private:
    unordered_map<string, int> memo;
    
    int dp(int i, int k, char prevChar, int prevCount, string& s) {
        if (k < 0) {
            return INT_MAX;
        }
        if (i == s.length()) {
            return 0;
        }
        
        string key = to_string(i) + "," + to_string(k) + "," + prevChar + "," + to_string(prevCount);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int deleteOp = dp(i + 1, k - 1, prevChar, prevCount, s);
        
        int keep;
        if (s[i] == prevChar) {
            keep = dp(i + 1, k, prevChar, prevCount + 1, s);
            if (prevCount == 1 || prevCount == 9 || prevCount == 99) {
                keep += 1;
            }
        } else {
            keep = 1 + dp(i + 1, k, s[i], 1, s);
        }
        
        int result = min(deleteOp, keep);
        memo[key] = result;
        return result;
    }
    
public:
    int getLengthOfOptimalCompression(string s, int k) {
        memo.clear();
        return dp(0, k, '\0', 0, s);
    }
};