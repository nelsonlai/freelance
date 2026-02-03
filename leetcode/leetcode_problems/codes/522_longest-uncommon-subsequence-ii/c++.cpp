/*
 * Problem: Longest Uncommon Subsequence II
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool isSubsequence(string s, string t) {
        int i = 0;
        for (char c : t) {
            if (i < s.length() && s[i] == c) {
                i++;
            }
        }
        return i == s.length();
    }

public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
            return a.length() > b.length();
        });
        
        for (int i = 0; i < strs.size(); i++) {
            bool isUncommon = true;
            for (int j = 0; j < strs.size(); j++) {
                if (i != j && isSubsequence(strs[i], strs[j])) {
                    isUncommon = false;
                    break;
                }
            }
            if (isUncommon) {
                return strs[i].length();
            }
        }
        
        return -1;
    }
};