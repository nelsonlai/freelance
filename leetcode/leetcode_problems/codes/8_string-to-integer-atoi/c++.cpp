/*
 * Problem: String to Integer (atoi)
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <climits>
#include <cctype>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        while (i < s.length() && s[i] == ' ') {
            i++;
        }
        
        if (i >= s.length()) {
            return 0;
        }
        
        int sign = 1;
        if (s[i] == '-') {
            sign = -1;
            i++;
        } else if (s[i] == '+') {
            i++;
        }
        
        int result = 0;
        while (i < s.length() && isdigit(s[i])) {
            int digit = s[i] - '0';
            if (result > INT_MAX / 10 || 
                (result == INT_MAX / 10 && digit > 7)) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            result = result * 10 + digit;
            i++;
        }
        
        return sign * result;
    }
};