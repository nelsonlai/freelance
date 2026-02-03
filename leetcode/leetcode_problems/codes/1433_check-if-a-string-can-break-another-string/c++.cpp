/*
 * Problem: Check If a String Can Break Another String
 * Difficulty: Medium
 * Tags: string, greedy, sort
 * 
 * Approach: Sort both strings, check if s1 >= s2 or s2 >= s1 at all positions
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for sorted strings
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        
        bool s1Breaks = true;
        bool s2Breaks = true;
        
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] < s2[i]) {
                s1Breaks = false;
            }
            if (s2[i] < s1[i]) {
                s2Breaks = false;
            }
        }
        
        return s1Breaks || s2Breaks;
    }
};