/**
 * Problem: Find Root of N-Ary Tree
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Root appears once, all other nodes appear as children. Use set to track children
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for set
 */

import java.util.*;

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

class Solution {
    public Node findRoot(List<Node> tree) {
        Set<Node> childrenSet = new HashSet<>();
        for (Node node : tree) {
            for (Node child : node.children) {
                childrenSet.add(child);
            }
        }
        
        for (Node node : tree) {
            if (!childrenSet.contains(node)) {
                return node;
            }
        }
        return null;
    }
}