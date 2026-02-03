/*
 * Problem: Delete Characters to Make Fancy String
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Remove characters that appear 3+ times consecutively
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>

using namespace std;

class Solution {
public:
    string makeFancyString(string s) {
        string result;
        for (char c : s) {
            int len = result.length();
            if (len >= 2 && result[len - 1] == c && result[len - 2] == c) {
                continue;
            }
            result += c;
        }
        return result;
    }
};