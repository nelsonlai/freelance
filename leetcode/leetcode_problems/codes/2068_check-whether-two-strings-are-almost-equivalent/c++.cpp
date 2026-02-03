/*
 * Problem: Check Whether Two Strings are Almost Equivalent
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: Count character frequencies and check if difference <= 3 for all characters
 * Time Complexity: O(n + m) where n, m are string lengths
 * Space Complexity: O(26)
 */

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

class Solution {
public:
    bool checkAlmostEquivalent(string word1, string word2) {
        unordered_map<char, int> count1, count2;
        
        for (char c : word1) {
            count1[c]++;
        }
        for (char c : word2) {
            count2[c]++;
        }
        
        unordered_set<char> allChars;
        for (auto& p : count1) {
            allChars.insert(p.first);
        }
        for (auto& p : count2) {
            allChars.insert(p.first);
        }
        
        for (char c : allChars) {
            int diff = abs(count1[c] - count2[c]);
            if (diff > 3) {
                return false;
            }
        }
        
        return true;
    }
};