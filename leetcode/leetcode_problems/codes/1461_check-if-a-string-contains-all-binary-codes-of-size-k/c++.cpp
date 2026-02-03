/*
 * Problem: Check If a String Contains All Binary Codes of Size K
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Extract all substrings of length k, check if we have 2^k unique codes
 * Time Complexity: O(n * k) where n is length of s
 * Space Complexity: O(2^k) for set
 */

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> seen;
        for (int i = 0; i <= (int)s.length() - k; i++) {
            seen.insert(s.substr(i, k));
        }
        return seen.size() == (1 << k);
    }
};