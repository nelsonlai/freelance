/*
 * Problem: Check If String Is a Prefix of Array
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Concatenate words and check if equals s
 * Time Complexity: O(n * m) where n is words, m is avg length
 * Space Complexity: O(n * m)
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isPrefixString(string s, vector<string>& words) {
        string concatenated;
        for (string& word : words) {
            concatenated += word;
            if (concatenated == s) {
                return true;
            }
            if (concatenated.length() >= s.length()) {
                return false;
            }
        }
        return false;
    }
};