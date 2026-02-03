/**
 * Problem: Zigzag Conversion
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

function convert(s: string, numRows: number): string {
    if (numRows === 1 || numRows >= s.length) {
        return s;
    }
    
    const rows: string[] = new Array(numRows).fill('');
    let currentRow = 0;
    let goingDown = false;
    
    for (const char of s) {
        rows[currentRow] += char;
        if (currentRow === 0 || currentRow === numRows - 1) {
            goingDown = !goingDown;
        }
        currentRow += goingDown ? 1 : -1;
    }
    
    return rows.join('');
};