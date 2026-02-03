/*
 * Problem: Shortest Palindrome
 * Difficulty: Hard
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.empty()) {
            return s;
        }
        
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        for (int i = 0; i < s.length(); i++) {
            if (s.substr(0, s.length() - i) == rev.substr(i)) {
                return rev.substr(0, i) + s;
            }
        }
        
        return rev + s;
    }
};