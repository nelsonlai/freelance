/*
 * Problem: Reverse Words in a String III
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        istringstream iss(s);
        string word;
        string result = "";
        
        while (iss >> word) {
            reverse(word.begin(), word.end());
            if (!result.empty()) {
                result += " ";
            }
            result += word;
        }
        
        return result;
    }
};