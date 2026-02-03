/**
 * Problem: Verify Preorder Serialization of a Binary Tree
 * Difficulty: Medium
 * Tags: string, tree, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public boolean isValidSerialization(String preorder) {
        String[] nodes = preorder.split(",");
        int slots = 1;
        
        for (String node : nodes) {
            slots--;
            if (slots < 0) {
                return false;
            }
            if (!node.equals("#")) {
                slots += 2;
            }
        }
        
        return slots == 0;
    }
}