/*
 * Problem: Length of Last Word
 * Difficulty: Easy
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string.h>
#include <ctype.h>

int lengthOfLastWord(char* s) {
    int length = 0;
    int i = strlen(s) - 1;
    
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