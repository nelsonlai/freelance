/**
 * Problem: Next Day
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

interface Date {
    nextDay(): string;
}

Date.prototype.nextDay = function(): string {
    
}

/**
 * const date = new Date("2014-06-20");
 * date.nextDay(); // "2014-06-21"
 */