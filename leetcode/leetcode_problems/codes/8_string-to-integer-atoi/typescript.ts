/**
 * Problem: String to Integer (atoi)
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function myAtoi(s: string): number {
    s = s.trim();
    if (s.length === 0) {
        return 0;
    }
    
    let sign = 1;
    let i = 0;
    
    if (s[0] === '-') {
        sign = -1;
        i = 1;
    } else if (s[0] === '+') {
        i = 1;
    }
    
    const INT_MAX = Math.pow(2, 31) - 1;
    const INT_MIN = -Math.pow(2, 31);
    let result = 0;
    
    while (i < s.length && /^\d$/.test(s[i])) {
        const digit = parseInt(s[i]);
        if (result > Math.floor(INT_MAX / 10) || 
            (result === Math.floor(INT_MAX / 10) && digit > 7)) {
            return sign === 1 ? INT_MAX : INT_MIN;
        }
        result = result * 10 + digit;
        i++;
    }
    
    return sign * result;
};