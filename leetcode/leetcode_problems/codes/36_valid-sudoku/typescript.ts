/**
 * Problem: Valid Sudoku
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

function isValidSudoku(board: string[][]): boolean {
    const seen = new Set<string>();
    
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            if (board[i][j] !== '.') {
                const num = board[i][j];
                const rowKey = `row-${i}-${num}`;
                const colKey = `col-${j}-${num}`;
                const boxKey = `box-${Math.floor(i / 3)}-${Math.floor(j / 3)}-${num}`;
                
                if (seen.has(rowKey) || seen.has(colKey) || seen.has(boxKey)) {
                    return false;
                }
                
                seen.add(rowKey);
                seen.add(colKey);
                seen.add(boxKey);
            }
        }
    }
    
    return true;
};