/*
 * Problem: Largest Odd Number in String
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Find rightmost odd digit, return substring up to that digit
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <string>

using namespace std;

class Solution {
public:
    string largestOddNumber(string num) {
        for (int i = num.length() - 1; i >= 0; i--) {
            if ((num[i] - '0') % 2 == 1) {
                return num.substr(0, i + 1);
            }
        }
        return "";
    }
};