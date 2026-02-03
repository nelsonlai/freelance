/**
 * Problem: Letter Combinations of a Phone Number
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

/**
 * @param {string} digits
 * @return {string[]}
 */
var letterCombinations = function(digits) {
    if (!digits || digits.length === 0) {
        return [];
    }
    
    const phoneMap = {
        '2': 'abc', '3': 'def', '4': 'ghi', '5': 'jkl',
        '6': 'mno', '7': 'pqrs', '8': 'tuv', '9': 'wxyz'
    };
    
    const result = [];
    
    function backtrack(index, current) {
        if (index === digits.length) {
            result.push(current);
            return;
        }
        
        const letters = phoneMap[digits[index]];
        for (let i = 0; i < letters.length; i++) {
            backtrack(index + 1, current + letters[i]);
        }
    }
    
    backtrack(0, "");
    return result;
};