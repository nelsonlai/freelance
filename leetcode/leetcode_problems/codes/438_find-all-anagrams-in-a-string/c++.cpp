/*
 * Problem: Find All Anagrams in a String
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if (s.length() < p.length()) {
            return result;
        }
        
        vector<int> pCount(26, 0);
        for (char c : p) {
            pCount[c - 'a']++;
        }
        
        vector<int> windowCount(26, 0);
        for (int i = 0; i < p.length(); i++) {
            windowCount[s[i] - 'a']++;
        }
        
        if (pCount == windowCount) {
            result.push_back(0);
        }
        
        for (int i = p.length(); i < s.length(); i++) {
            windowCount[s[i] - 'a']++;
            windowCount[s[i - p.length()] - 'a']--;
            
            if (pCount == windowCount) {
                result.push_back(i - p.length() + 1);
            }
        }
        
        return result;
    }
};