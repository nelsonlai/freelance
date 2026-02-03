/**
 * Problem: Serialize and Deserialize BST
 * Difficulty: Medium
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
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

public class Codec {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if (root == null) {
            return "";
        }
        
        List<String> result = new ArrayList<>();
        preorder(root, result);
        return String.join(",", result);
    }
    
    private void preorder(TreeNode node, List<String> result) {
        if (node != null) {
            result.add(String.valueOf(node.val));
            preorder(node.left, result);
            preorder(node.right, result);
        }
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if (data.isEmpty()) {
            return null;
        }
        
        String[] values = data.split(",");
        List<Integer> nums = new ArrayList<>();
        for (String val : values) {
            nums.add(Integer.parseInt(val));
        }
        
        return build(nums, Long.MIN_VALUE, Long.MAX_VALUE);
    }
    
    private TreeNode build(List<Integer> values, long minVal, long maxVal) {
        if (values.isEmpty() || values.get(0) < minVal || values.get(0) > maxVal) {
            return null;
        }
        
        int val = values.remove(0);
        TreeNode node = new TreeNode(val);
        node.left = build(values, minVal, val);
        node.right = build(values, val, maxVal);
        return node;
    }
}

// Your Codec object will be instantiated and called as such:
// Codec ser = new Codec();
// Codec deser = new Codec();
// String tree = ser.serialize(root);
// TreeNode ans = deser.deserialize(tree);
// return ans;