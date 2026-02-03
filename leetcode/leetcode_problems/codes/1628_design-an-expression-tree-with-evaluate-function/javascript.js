/**
 * Problem: Design an Expression Tree With Evaluate Function
 * Difficulty: Medium
 * Tags: array, tree, math, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

var Node = function () {
  if (this.constructor === Node) {
    throw new Error('Cannot instanciate abstract class');
  }
};

Node.prototype.evaluate = function () {
  throw new Error('Cannot call abstract method')
};

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input 
 * and returns the expression tree representing it as a Node.
 */

class TreeBuilder{
	/**
     * @param {string[]} s
     * @return {Node}
     */
	buildTree(postfix) {
    	
	}
    
}

/**
 * Your TreeBuilder object will be instantiated and called as such:
 * var obj = new TreeBuilder();
 * var expTree = obj.buildTree(postfix);
 * var ans = expTree.evaluate();
 */