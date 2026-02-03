/**
 * Problem: Make Object Immutable
 * Difficulty: Medium
 * Tags: array, string, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

type JSONValue = null | boolean | number | string | JSONValue[] | { [key: string]: JSONValue };
type Obj = Array<JSONValue> | Record<string, JSONValue>;

function makeImmutable(obj: Obj): Obj {
    
};

/**
 * const obj = makeImmutable({x: 5});
 * obj.x = 6; // throws "Error Modifying x"
 */