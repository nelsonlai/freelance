/**
 * Problem: Longest Palindromic Substring
 * Difficulty: Medium
 * Tags: array, string, tree, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function(s) {
    if (!s || s.length === 0) return "";
    
    let start = 0, maxLen = 1;
    
    function expandAroundCenter(left, right) {
        while (left >= 0 && right < s.length && s[left] === s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
    
    for (let i = 0; i < s.length; i++) {
        const len1 = expandAroundCenter(i, i);
        const len2 = expandAroundCenter(i, i + 1);
        const len = Math.max(len1, len2);
        
        if (len > maxLen) {
            start = i - Math.floor((len - 1) / 2);
            maxLen = len;
        }
    }
    
    return s.substring(start, start + maxLen);
};