/*
 * Problem: Get Equal Substrings Within Budget
 * Difficulty: Medium
 * Tags: array, string, tree, search
 * 
 * Approach: Sliding window - find longest substring where cost <= maxCost
 * Time Complexity: O(n) where n is the length of strings
 * Space Complexity: O(1)
 */
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int left = 0;
        int currentCost = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            currentCost += abs(s[right] - t[right]);
            
            while (currentCost > maxCost) {
                currentCost -= abs(s[left] - t[left]);
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};