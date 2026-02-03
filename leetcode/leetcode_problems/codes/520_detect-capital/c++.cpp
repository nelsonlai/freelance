/*
 * Problem: Detect Capital
 * Difficulty: Easy
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
    bool detectCapitalUse(string word) {
        if (word.length() <= 1) {
            return true;
        }
        
        if (isupper(word[0])) {
            return allUpperCase(word.substr(1)) || allLowerCase(word.substr(1));
        } else {
            return allLowerCase(word.substr(1));
        }
    }
    
private:
    bool allUpperCase(string s) {
        for (char c : s) {
            if (!isupper(c)) {
                return false;
            }
        }
        return true;
    }
    
    bool allLowerCase(string s) {
        for (char c : s) {
            if (!islower(c)) {
                return false;
            }
        }
        return true;
    }
};