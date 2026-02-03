/*
 * Problem: Check if All Characters Have Equal Number of Occurrences
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: Count occurrences, check if all equal
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1) - fixed 26 characters
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool areOccurrencesEqual(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        int first = -1;
        for (int c : count) {
            if (c > 0) {
                if (first == -1) {
                    first = c;
                } else if (c != first) {
                    return false;
                }
            }
        }
        
        return true;
    }
};