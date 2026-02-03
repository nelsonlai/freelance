/*
 * Problem: Reverse Prefix of Word
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Find first occurrence of ch, reverse prefix up to that index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reversePrefix(string word, char ch) {
        size_t idx = word.find(ch);
        if (idx == string::npos) {
            return word;
        }
        
        reverse(word.begin(), word.begin() + idx + 1);
        return word;
    }
};