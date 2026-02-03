/**
 * Problem: Move Sub-Tree of N-Ary Tree
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
        children = new ArrayList<Node>();
    }
    
    public Node(int _val) {
        val = _val;
        children = new ArrayList<Node>();
    }
    
    public Node(int _val,ArrayList<Node> _children) {
        val = _val;
        children = _children;
    }
};
*/

import java.util.*;

class Solution {
    public Node moveSubTree(Node root, Node p, Node q) {
        if (p == q) {
            return root;
        }
        
        Node pParent = findParent(root, p, null);
        
        if (isDescendant(p, q)) {
            Node qParent = findParent(root, q, null);
            qParent.children.remove(q);
            if (pParent != null) {
                pParent.children.remove(p);
                pParent.children.add(q);
            } else {
                root = q;
            }
            q.children.add(p);
        } else {
            if (pParent != null) {
                pParent.children.remove(p);
            } else {
                root = null;
            }
            q.children.add(p);
        }
        
        return root != null ? root : p;
    }
    
    private Node findParent(Node node, Node target, Node parent) {
        if (node == target) {
            return parent;
        }
        for (Node child : node.children) {
            Node result = findParent(child, target, node);
            if (result != null) {
                return result;
            }
        }
        return null;
    }
    
    private boolean isDescendant(Node node, Node target) {
        if (node == target) {
            return true;
        }
        for (Node child : node.children) {
            if (isDescendant(child, target)) {
                return true;
            }
        }
        return false;
    }
}