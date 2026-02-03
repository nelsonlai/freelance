/**
 * Problem: Serialize and Deserialize N-ary Tree
 * Difficulty: Hard
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for _Node.
 * class _Node {
 *     val: number
 *     children: _Node[]
 *     
 *     constructor(v: number) {
 *         this.val = v;
 *         this.children = [];
 *     }
 * }
 */


class Codec {
  	constructor() {
        
    }
    
    // Encodes a tree to a single string.
    serialize(root: _Node | null): string {
        
    };
	
    // Decodes your encoded data to tree.
    deserialize(data: string): _Node | null {
        
    };
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));