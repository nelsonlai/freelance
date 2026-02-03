/**
 * Problem: N-ary Tree Preorder Traversal
 * Difficulty: Easy
 * Tags: tree, search, stack
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/*
// Definition for a Node.
class Node {
    public int val;
    public List<Node> children;

    public Node() {}

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, List<Node> _children) {
        val = _val;
        children = _children;
    }
};
*/

import java.util.*;

class Solution {
    public List<Integer> preorder(Node root) {
        if (root == null) {
            return new ArrayList<>();
        }
        
        List<Integer> result = new ArrayList<>();
        result.add(root.val);
        
        if (root.children != null) {
            for (Node child : root.children) {
                result.addAll(preorder(child));
            }
        }
        
        return result;
    }
}