/*
 * Problem: Minimum Number of Frogs Croaking
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: Track count of each letter in 'croak', need max concurrent frogs
 * Time Complexity: O(n) where n is length of string
 * Space Complexity: O(1)
 */

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        int count[5] = {0};
        int maxFrogs = 0;
        int activeFrogs = 0;
        
        unordered_map<char, int> charToIndex = {{'c', 0}, {'r', 1}, {'o', 2}, {'a', 3}, {'k', 4}};
        
        for (char c : croakOfFrogs) {
            if (charToIndex.find(c) == charToIndex.end()) {
                return -1;
            }
            
            int idx = charToIndex[c];
            count[idx]++;
            
            if (c == 'c') {
                activeFrogs++;
                maxFrogs = max(maxFrogs, activeFrogs);
            } else if (c == 'k') {
                activeFrogs--;
            }
            
            if (!(count[0] >= count[1] && count[1] >= count[2] && 
                  count[2] >= count[3] && count[3] >= count[4])) {
                return -1;
            }
        }
        
        return activeFrogs == 0 ? maxFrogs : -1;
    }
};