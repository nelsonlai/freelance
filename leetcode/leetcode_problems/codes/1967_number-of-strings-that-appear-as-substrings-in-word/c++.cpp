/*
 * Problem: Number of Strings That Appear as Substrings in Word
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Check if each pattern is a substring of word
 * Time Complexity: O(n * m) where n is patterns, m is word length
 * Space Complexity: O(1)
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;
        for (string& pattern : patterns) {
            if (word.find(pattern) != string::npos) {
                count++;
            }
        }
        return count;
    }
};