/*
 * Problem: Construct K Palindrome Strings
 * Difficulty: Medium
 * Tags: string, greedy, hash
 * 
 * Approach: Count character frequencies, need at least k palindromes, at most one odd per palindrome
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1) for character counts
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool canConstruct(string s, int k) {
        if (s.length() < k) {
            return false;
        }
        
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        int oddCount = 0;
        for (int count : freq) {
            if (count % 2 == 1) {
                oddCount++;
            }
        }
        
        return oddCount <= k;
    }
};