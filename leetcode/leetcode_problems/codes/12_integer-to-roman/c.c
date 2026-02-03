/*
 * Problem: Integer to Roman
 * Difficulty: Medium
 * Tags: string, math, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    char* result = (char*)malloc(20 * sizeof(char));
    result[0] = '\0';
    
    for (int i = 0; i < 13; i++) {
        int count = num / values[i];
        for (int j = 0; j < count; j++) {
            strcat(result, symbols[i]);
        }
        num %= values[i];
    }
    
    return result;
}