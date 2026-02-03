/**
 * Problem: Add Binary
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {string} a
 * @param {string} b
 * @return {string}
 */
var addBinary = function(a, b) {
    const result = [];
    let carry = 0;
    let i = a.length - 1;
    let j = b.length - 1;
    
    while (i >= 0 || j >= 0 || carry > 0) {
        let total = carry;
        if (i >= 0) {
            total += parseInt(a[i--]);
        }
        if (j >= 0) {
            total += parseInt(b[j--]);
        }
        result.push(total % 2);
        carry = Math.floor(total / 2);
    }
    
    return result.reverse().join('');
};