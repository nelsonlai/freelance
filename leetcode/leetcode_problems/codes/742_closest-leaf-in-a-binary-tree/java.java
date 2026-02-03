import java.util.*;

class Solution {
    public int findClosestLeaf(TreeNode root, int k) {
        Map<Integer, List<Integer>> graph = new HashMap<>();
        Set<Integer> leaves = new HashSet<>();
        
        buildGraph(root, null, graph, leaves);
        
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();
        queue.offer(k);
        visited.add(k);
        
        while (!queue.isEmpty()) {
            int node = queue.poll();
            if (leaves.contains(node)) {
                return node;
            }
            for (int neighbor : graph.getOrDefault(node, Collections.emptyList())) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.offer(neighbor);
                }
            }
        }
        
        return -1;
    }
    
    private void buildGraph(TreeNode node, TreeNode parent, Map<Integer, List<Integer>> graph, Set<Integer> leaves) {
        if (node == null) return;
        if (parent != null) {
            graph.computeIfAbsent(node.val, k -> new ArrayList<>()).add(parent.val);
        }
        if (node.left != null) {
            graph.computeIfAbsent(node.val, k -> new ArrayList<>()).add(node.left.val);
            buildGraph(node.left, node, graph, leaves);
        }
        if (node.right != null) {
            graph.computeIfAbsent(node.val, k -> new ArrayList<>()).add(node.right.val);
            buildGraph(node.right, node, graph, leaves);
        }
        if (node.left == null && node.right == null) {
            leaves.add(node.val);
        }
    }
}
