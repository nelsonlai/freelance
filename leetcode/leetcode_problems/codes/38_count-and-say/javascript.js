/**
 * Problem: Count and Say
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * @param {number} n
 * @return {string}
 */
var countAndSay = function(n) {
    if (n === 1) {
        return "1";
    }
    
    let result = "1";
    for (let i = 1; i < n; i++) {
        let newResult = "";
        let j = 0;
        while (j < result.length) {
            let count = 1;
            while (j + 1 < result.length && result[j] === result[j + 1]) {
                count++;
                j++;
            }
            newResult += count.toString();
            newResult += result[j];
            j++;
        }
        result = newResult;
    }
    
    return result;
};