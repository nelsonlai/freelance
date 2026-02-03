/**
 * Problem: Multiply Strings
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function multiply(num1: string, num2: string): string {
    if (num1 === "0" || num2 === "0") {
        return "0";
    }
    
    const m = num1.length, n = num2.length;
    const result: number[] = new Array(m + n).fill(0);
    
    for (let i = m - 1; i >= 0; i--) {
        for (let j = n - 1; j >= 0; j--) {
            const mul = parseInt(num1[i]) * parseInt(num2[j]);
            const p1 = i + j, p2 = i + j + 1;
            const total = mul + result[p2];
            
            result[p2] = total % 10;
            result[p1] += Math.floor(total / 10);
        }
    }
    
    // Remove leading zeros
    let start = 0;
    while (start < result.length && result[start] === 0) {
        start++;
    }
    
    return result.slice(start).join('');
};