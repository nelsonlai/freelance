/**
 * Problem: Array Prototype Last
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

interface Array<T> {
    last(): T | -1;
}

Array.prototype.last = function() {
    
};

/**
 * const arr = [1, 2, 3];
 * arr.last(); // 3
 */