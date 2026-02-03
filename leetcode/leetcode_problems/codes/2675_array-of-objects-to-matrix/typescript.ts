/**
 * Problem: Array of Objects to Matrix
 * Difficulty: Hard
 * Tags: array, string, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

type JSONValue = null | boolean | number | string | JSONValue[] | { [key: string]: JSONValue };

function jsonToMatrix(arr: JSONValue[]): (null | boolean | number | string)[][] {
    
};