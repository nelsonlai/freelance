/*
 * Problem: Find the Index of the First Occurrence in a String
 * Difficulty: Easy
 * Tags: array, string, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        
        int n = haystack.length();
        int m = needle.length();
        
        for (int i = 0; i <= n - m; i++) {
            if (haystack.substr(i, m) == needle) {
                return i;
            }
        }
        
        return -1;
    }
};