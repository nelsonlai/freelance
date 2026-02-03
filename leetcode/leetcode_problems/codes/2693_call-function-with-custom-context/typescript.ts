/**
 * Problem: Call Function with Custom Context
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

type JSONValue = null | boolean | number | string | JSONValue[] | { [key: string]: JSONValue };

interface Function {
    callPolyfill(context: Record<string, JSONValue>, ...args: JSONValue[]): JSONValue;
}


Function.prototype.callPolyfill = function(context, ...args): JSONValue {
    
}

/**
 * function increment() { this.count++; return this.count; }
 * increment.callPolyfill({count: 1}); // 2
 */