/**
 * Problem: Convert Binary Search Tree to Sorted Doubly Linked List
 * Difficulty: Medium
 * Tags: tree, sort, search, linked_list, stack
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/*
// Definition for a Node.
class Node {
    public int val;
    public Node left;
    public Node right;

    public Node() {
        // TODO: Implement optimized solution
        return 0;
    }

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val,Node _left,Node _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
    private Node first = null;
    private Node last = null;
    
    public Node treeToDoublyList(Node root) {
        if (root == null) {
            return null;
        }
        
        inorder(root);
        
        first.left = last;
        last.right = first;
        
        return first;
    }
    
    private void inorder(Node node) {
        if (node != null) {
            inorder(node.left);
            
            if (last != null) {
                last.right = node;
                node.left = last;
            } else {
                first = node;
            }
            last = node;
            
            inorder(node.right);
        }
    }
}