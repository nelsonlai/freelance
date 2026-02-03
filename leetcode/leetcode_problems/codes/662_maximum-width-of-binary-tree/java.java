import java.util.*;

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public int widthOfBinaryTree(TreeNode root) {
        if (root == null) {
            return 0;
        }
        
        Queue<Pair<TreeNode, Long>> queue = new LinkedList<>();
        queue.offer(new Pair<>(root, 0L));
        int maxWidth = 0;
        
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            long leftPos = queue.peek().getValue();
            
            for (int i = 0; i < levelSize; i++) {
                Pair<TreeNode, Long> pair = queue.poll();
                TreeNode node = pair.getKey();
                long pos = pair.getValue();
                
                if (node.left != null) {
                    queue.offer(new Pair<>(node.left, 2 * pos));
                }
                if (node.right != null) {
                    queue.offer(new Pair<>(node.right, 2 * pos + 1));
                }
            }
            
            if (!queue.isEmpty()) {
                long rightPos = ((LinkedList<Pair<TreeNode, Long>>)queue).getLast().getValue();
                maxWidth = Math.max(maxWidth, (int)(rightPos - leftPos + 1));
            }
        }
        
        return maxWidth;
    }
}

class Pair<K, V> {
    private K key;
    private V value;
    
    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }
    
    public K getKey() {
        return key;
    }
    
    public V getValue() {
        return value;
    }
}
