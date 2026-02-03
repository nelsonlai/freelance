import java.util.*;

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    private Map<Integer, List<Integer>> graph = new HashMap<>();
    
    public List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        buildGraph(root, null);
        
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(target.val);
        Set<Integer> visited = new HashSet<>();
        visited.add(target.val);
        int level = 0;
        
        while (!queue.isEmpty() && level < k) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int node = queue.poll();
                for (int neighbor : graph.getOrDefault(node, Collections.emptyList())) {
                    if (!visited.contains(neighbor)) {
                        visited.add(neighbor);
                        queue.offer(neighbor);
                    }
                }
            }
            level++;
        }
        
        return new ArrayList<>(queue);
    }
    
    private void buildGraph(TreeNode node, TreeNode parent) {
        if (node == null) {
            return;
        }
        if (parent != null) {
            graph.computeIfAbsent(node.val, k -> new ArrayList<>()).add(parent.val);
            graph.computeIfAbsent(parent.val, k -> new ArrayList<>()).add(node.val);
        }
        buildGraph(node.left, node);
        buildGraph(node.right, node);
    }
}
