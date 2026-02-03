/*
 * Problem: Permutation in String
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        
        vector<int> s1Count(26, 0);
        vector<int> windowCount(26, 0);
        
        for (char c : s1) {
            s1Count[c - 'a']++;
        }
        
        for (int i = 0; i < s2.length(); i++) {
            windowCount[s2[i] - 'a']++;
            
            if (i >= s1.length()) {
                windowCount[s2[i - s1.length()] - 'a']--;
            }
            
            if (s1Count == windowCount) {
                return true;
            }
        }
        
        return false;
    }
};