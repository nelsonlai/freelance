/**
 * Problem: Clone Binary Tree With Random Pointer
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: DFS - create mapping, clone nodes, set random pointers
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for mapping
 */

import java.util.*;

/**
 * Definition for Node.
 * public class Node {
 *     int val;
 *     Node left;
 *     Node right;
 *     Node random;
 *     Node() {}
 *     Node(int val) { this.val = val; }
 *     Node(int val, Node left, Node right, Node random) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *         this.random = random;
 *     }
 * }
 */

class Solution {
    private Map<Node, NodeCopy> mapping = new HashMap<>();
    
    private NodeCopy clone(Node node) {
        if (node == null) {
            return null;
        }
        
        if (mapping.containsKey(node)) {
            return mapping.get(node);
        }
        
        NodeCopy new_node = new NodeCopy(node.val);
        mapping.put(node, new_node);
        
        new_node.left = clone(node.left);
        new_node.right = clone(node.right);
        new_node.random = clone(node.random);
        
        return new_node;
    }
    
    public NodeCopy copyRandomBinaryTree(Node root) {
        return clone(root);
    }
}
