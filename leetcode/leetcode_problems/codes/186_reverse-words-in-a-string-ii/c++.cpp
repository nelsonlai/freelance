/*
 * Problem: Reverse Words in a String II
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void reverseWords(vector<char>& s) {
        reverse(s.begin(), s.end());
        
        int start = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }
        }
        reverse(s.begin() + start, s.end());
    }
};