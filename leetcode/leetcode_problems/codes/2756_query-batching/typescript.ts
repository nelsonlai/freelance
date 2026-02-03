/**
 * Problem: Query Batching
 * Difficulty: Hard
 * Tags: array, string, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

type QueryMultiple = (keys: string[]) => Promise<string[]>

class QueryBatcher {
    
    constructor(queryMultiple: QueryMultiple, t: number) {
        
    }
    
    async getValue(key: string): Promise<string> {
        
    }
};

/**
 * async function queryMultiple(keys) { 
 *   return keys.map(key => key + '!');
 * }
 *
 * const batcher = new QueryBatcher(queryMultiple, 100);
 * batcher.getValue('a').then(console.log); // resolves "a!" at t=0ms 
 * batcher.getValue('b').then(console.log); // resolves "b!" at t=100ms 
 * batcher.getValue('c').then(console.log); // resolves "c!" at t=100ms 
 */