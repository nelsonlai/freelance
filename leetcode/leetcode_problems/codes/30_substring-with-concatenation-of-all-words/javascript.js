/**
 * Problem: Substring with Concatenation of All Words
 * Difficulty: Hard
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * @param {string} s
 * @param {string[]} words
 * @return {number[]}
 */
var findSubstring = function(s, words) {
    const result = [];
    if (!s || !words || words.length === 0) {
        return result;
    }
    
    const wordLen = words[0].length;
    const wordCount = {};
    for (const word of words) {
        wordCount[word] = (wordCount[word] || 0) + 1;
    }
    
    for (let i = 0; i < wordLen; i++) {
        let left = i;
        const seen = {};
        let count = 0;
        
        for (let j = i; j <= s.length - wordLen; j += wordLen) {
            const word = s.substring(j, j + wordLen);
            
            if (wordCount[word]) {
                seen[word] = (seen[word] || 0) + 1;
                count++;
                
                while (seen[word] > wordCount[word]) {
                    const leftWord = s.substring(left, left + wordLen);
                    seen[leftWord]--;
                    count--;
                    left += wordLen;
                }
                
                if (count === words.length) {
                    result.push(left);
                    const leftWord = s.substring(left, left + wordLen);
                    seen[leftWord]--;
                    count--;
                    left += wordLen;
                }
            } else {
                Object.keys(seen).forEach(key => delete seen[key]);
                count = 0;
                left = j + wordLen;
            }
        }
    }
    
    return result;
};