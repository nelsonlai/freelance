/**
 * Problem: Group Anagrams
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

function groupAnagrams(strs: string[]): string[][] {
    const groups: { [key: string]: string[] } = {};
    for (const s of strs) {
        const key = s.split('').sort().join('');
        if (!groups[key]) {
            groups[key] = [];
        }
        groups[key].push(s);
    }
    return Object.values(groups);
};