/*
 * Problem: Perform String Shifts
 * Difficulty: Easy
 * Tags: array, string, math
 * 
 * Approach: Calculate net shift amount, rotate string
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(n) for result
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int totalShift = 0;
        for (auto& sh : shift) {
            if (sh[0] == 0) {
                totalShift -= sh[1];
            } else {
                totalShift += sh[1];
            }
        }
        
        totalShift %= (int)s.length();
        if (totalShift < 0) {
            totalShift += s.length();
        }
        
        return s.substr(s.length() - totalShift) + s.substr(0, s.length() - totalShift);
    }
};