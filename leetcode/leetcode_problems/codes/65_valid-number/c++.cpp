/*
 * Problem: Valid Number
 * Difficulty: Hard
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        // Trim whitespace
        int start = 0, end = s.length() - 1;
        while (start <= end && s[start] == ' ') start++;
        while (end >= start && s[end] == ' ') end--;
        if (start > end) return false;
        s = s.substr(start, end - start + 1);
        
        bool seenDigit = false;
        bool seenDot = false;
        bool seenExp = false;
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (isdigit(c)) {
                seenDigit = true;
            } else if (c == '.') {
                if (seenDot || seenExp) {
                    return false;
                }
                seenDot = true;
            } else if (c == 'e' || c == 'E') {
                if (seenExp || !seenDigit) {
                    return false;
                }
                seenExp = true;
                seenDigit = false;
            } else if (c == '+' || c == '-') {
                if (i != 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
                    return false;
                }
            } else {
                return false;
            }
        }
        
        return seenDigit;
    }
};