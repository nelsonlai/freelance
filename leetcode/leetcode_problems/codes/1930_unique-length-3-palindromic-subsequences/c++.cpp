/*
 * Problem: Unique Length-3 Palindromic Subsequences
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: For each character, find first and last occurrence, count unique middle chars
 * Time Complexity: O(n * 26) where n is length
 * Space Complexity: O(26)
 */

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        unordered_map<char, int> first, last;
        
        for (int i = 0; i < s.length(); i++) {
            if (first.find(s[i]) == first.end()) {
                first[s[i]] = i;
            }
            last[s[i]] = i;
        }
        
        int result = 0;
        for (auto& [c, f] : first) {
            if (f < last[c]) {
                unordered_set<char> middle;
                for (int i = f + 1; i < last[c]; i++) {
                    middle.insert(s[i]);
                }
                result += middle.size();
            }
        }
        
        return result;
    }
};