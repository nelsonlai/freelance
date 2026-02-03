/*
 * Problem: Reformat The String
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Separate digits and letters, interleave starting with larger group
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(n) for result
 */

#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Solution {
public:
    string reformat(string s) {
        vector<char> digits;
        vector<char> letters;
        
        for (char c : s) {
            if (isdigit(c)) {
                digits.push_back(c);
            } else {
                letters.push_back(c);
            }
        }
        
        if (abs((int)digits.size() - (int)letters.size()) > 1) {
            return "";
        }
        
        string result = "";
        if (digits.size() >= letters.size()) {
            for (int i = 0; i < letters.size(); i++) {
                result += digits[i];
                result += letters[i];
            }
            if (digits.size() > letters.size()) {
                result += digits.back();
            }
        } else {
            for (int i = 0; i < digits.size(); i++) {
                result += letters[i];
                result += digits[i];
            }
            result += letters.back();
        }
        
        return result;
    }
};