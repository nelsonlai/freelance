/*
 * Problem: Longest Uncommon Subsequence I
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a == b) {
            return -1;
        }
        return max(a.length(), b.length());
    }
};