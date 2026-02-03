/**
 * Problem: Encode N-ary Tree to Binary Tree
 * Difficulty: Hard
 * Tags: tree, search
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

    public Node() {
        // TODO: Implement optimized solution
        return 0;
    }

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, List<Node> _children) {
        val = _val;
        children = _children;
    }
};
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */

import java.util.*;

class Codec {
    // Encodes an n-ary tree to a binary tree.
    public TreeNode encode(Node root) {
        if (root == null) {
            return null;
        }
        
        TreeNode binaryRoot = new TreeNode(root.val);
        
        if (root.children != null && !root.children.isEmpty()) {
            binaryRoot.left = encode(root.children.get(0));
            TreeNode current = binaryRoot.left;
            for (int i = 1; i < root.children.size(); i++) {
                current.right = encode(root.children.get(i));
                current = current.right;
            }
        }
        
        return binaryRoot;
    }
	
    // Decodes your binary tree to an n-ary tree.
    public Node decode(TreeNode root) {
        if (root == null) {
            return null;
        }
        
        Node naryRoot = new Node(root.val, new ArrayList<>());
        
        if (root.left != null) {
            Node child = decode(root.left);
            naryRoot.children.add(child);
            TreeNode current = root.left;
            while (current.right != null) {
                child = decode(current.right);
                naryRoot.children.add(child);
                current = current.right;
            }
        }
        
        return naryRoot;
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.decode(codec.encode(root));