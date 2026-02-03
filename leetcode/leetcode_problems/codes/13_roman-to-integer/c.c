/*
 * Problem: Roman to Integer
 * Difficulty: Easy
 * Tags: string, math, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

int romanToInt(char* s) {
    int romanMap[256] = {0};
    romanMap['I'] = 1;
    romanMap['V'] = 5;
    romanMap['X'] = 10;
    romanMap['L'] = 50;
    romanMap['C'] = 100;
    romanMap['D'] = 500;
    romanMap['M'] = 1000;
    
    int result = 0;
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        int current = romanMap[s[i]];
        if (i < len - 1) {
            int next = romanMap[s[i + 1]];
            if (current < next) {
                result -= current;
            } else {
                result += current;
            }
        } else {
            result += current;
        }
    }
    
    return result;
}