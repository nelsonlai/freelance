/**
 * Problem: Serialize and Deserialize N-ary Tree
 * Difficulty: Hard
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
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

import java.util.*;

class Codec {
    // Encodes a tree to a single string.
    public String serialize(Node root) {
        if (root == null) {
            return "";
        }
        
        List<String> result = new ArrayList<>();
        dfsSerialize(root, result);
        return String.join(",", result);
    }
    
    private void dfsSerialize(Node node, List<String> result) {
        result.add(String.valueOf(node.val));
        result.add(String.valueOf(node.children.size()));
        for (Node child : node.children) {
            dfsSerialize(child, result);
        }
    }
	
    // Decodes your encoded data to tree.
    public Node deserialize(String data) {
        if (data.isEmpty()) {
            return null;
        }
        
        String[] values = data.split(",");
        int[] index = {0};
        return dfsDeserialize(values, index);
    }
    
    private Node dfsDeserialize(String[] values, int[] index) {
        if (index[0] >= values.length) {
            return null;
        }
        
        int val = Integer.parseInt(values[index[0]++]);
        int numChildren = Integer.parseInt(values[index[0]++]);
        
        List<Node> children = new ArrayList<>();
        for (int i = 0; i < numChildren; i++) {
            children.add(dfsDeserialize(values, index));
        }
        
        return new Node(val, children);
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));