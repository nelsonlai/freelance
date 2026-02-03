/*
 * Problem: Palindromic Substrings
 * Difficulty: Medium
 * Tags: array, string, tree, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <string>

using namespace std;

class Solution {
private:
    int count = 0;
    
    void expand(string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }

public:
    int countSubstrings(string s) {
        for (int i = 0; i < s.length(); i++) {
            expand(s, i, i);
            expand(s, i, i + 1);
        }
        return count;
    }
};