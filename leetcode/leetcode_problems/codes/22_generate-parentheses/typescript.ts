/**
 * Problem: Generate Parentheses
 * Difficulty: Medium
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

function generateParenthesis(n: number): string[] {
    const result: string[] = [];
    
    function backtrack(current: string, open: number, close: number): void {
        if (current.length === 2 * n) {
            result.push(current);
            return;
        }
        
        if (open < n) {
            backtrack(current + '(', open + 1, close);
        }
        
        if (close < open) {
            backtrack(current + ')', open, close + 1);
        }
    }
    
    backtrack("", 0, 0);
    return result;
};