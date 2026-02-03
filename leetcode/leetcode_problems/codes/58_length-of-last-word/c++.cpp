/*
 * Problem: Length of Last Word
 * Difficulty: Easy
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int length = 0;
        int i = s.length() - 1;
        
        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }
        
        // Count characters of last word
        while (i >= 0 && s[i] != ' ') {
            length++;
            i--;
        }
        
        return length;
    }
};