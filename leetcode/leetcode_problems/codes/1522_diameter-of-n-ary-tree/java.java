/**
 * Problem: Diameter of N-Ary Tree
 * Difficulty: Medium
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

class Solution {
    private int maxDiameter = 0;
    
    public int diameter(Node root) {
        maxDiameter = 0;
        dfs(root);
        return maxDiameter;
    }
    
    private int dfs(Node node) {
        if (node == null || node.children == null || node.children.isEmpty()) {
            return 0;
        }
        
        List<Integer> depths = new ArrayList<>();
        for (Node child : node.children) {
            depths.add(dfs(child));
        }
        
        depths.sort((a, b) -> Integer.compare(b, a));
        
        if (depths.size() >= 2) {
            maxDiameter = Math.max(maxDiameter, depths.get(0) + depths.get(1) + 2);
        } else if (depths.size() == 1) {
            maxDiameter = Math.max(maxDiameter, depths.get(0) + 1);
        }
        
        return depths.isEmpty() ? 0 : depths.get(0) + 1;
    }
}