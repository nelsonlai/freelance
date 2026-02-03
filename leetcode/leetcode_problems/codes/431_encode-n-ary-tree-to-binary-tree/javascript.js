/**
 * Problem: Encode N-ary Tree to Binary Tree
 * Difficulty: Hard
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * // Definition for a _Node.
 * function _Node(val,children) {
 *    this.val = val;
 *    this.children = children;
 * };
 */

/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */

class Codec {
  	constructor() {
    }
    
    /** 
     * @param {_Node|null} root
     * @return {TreeNode|null}
     */
    // Encodes an n-ary tree to a binary tree.
    encode = function(root) {
		
    };
	
    /** 
     * @param {TreeNode|null} root 
     * @return {_Node|null}
     */
    // Decodes your binary tree to an n-ary tree.
    decode = function(root) {
		
    };
}

/*
* Your Codec object will be instantiated and called as such:
* codec = Codec()
* codec.decode(codec.encode(root))
*/