/**
 * Problem: Longest Substring Without Repeating Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

function lengthOfLongestSubstring(s: string): number {
    const charIndex = new Map<string, number>();
    let left = 0;
    let maxLen = 0;
    
    for (let right = 0; right < s.length; right++) {
        const c = s[right];
        if (charIndex.has(c) && charIndex.get(c)! >= left) {
            left = charIndex.get(c)! + 1;
        }
        charIndex.set(c, right);
        maxLen = Math.max(maxLen, right - left + 1);
    }
    
    return maxLen;
};