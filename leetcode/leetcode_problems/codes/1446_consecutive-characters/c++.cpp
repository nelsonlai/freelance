/*
 * Problem: Consecutive Characters
 * Difficulty: Easy
 * Tags: string, tree
 * 
 * Approach: Track current consecutive length, update max
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1)
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPower(string s) {
        int maxPower = 1;
        int currentPower = 1;
        
        for (int i = 1; i < s.length(); i++) {
            if (s[i] == s[i - 1]) {
                currentPower++;
                maxPower = max(maxPower, currentPower);
            } else {
                currentPower = 1;
            }
        }
        
        return maxPower;
    }
};