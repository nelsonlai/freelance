/**
 * Problem: Build Binary Expression Tree From Infix Expression
 * Difficulty: Hard
 * Tags: string, tree, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a binary tree node.
 * class Node {
 *     char val;
 *     Node left;
 *     Node right;
 *     Node() {this.val = ' ';}
 *     Node(char val) { this.val = val; }
 *     Node(char val, Node left, Node right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
import java.util.*;

class Solution {
    public Node expTree(String s) {
        List<String> tokens = tokenize(s);
        return buildTree(tokens);
    }
    
    private List<String> tokenize(String s) {
        List<String> tokens = new ArrayList<>();
        int i = 0;
        while (i < s.length()) {
            if (Character.isDigit(s.charAt(i))) {
                StringBuilder num = new StringBuilder();
                while (i < s.length() && Character.isDigit(s.charAt(i))) {
                    num.append(s.charAt(i));
                    i++;
                }
                tokens.add(num.toString());
            } else {
                tokens.add(String.valueOf(s.charAt(i)));
                i++;
            }
        }
        return tokens;
    }
    
    private int getPriority(String op) {
        if (op.equals("+") || op.equals("-")) {
            return 1;
        }
        if (op.equals("*") || op.equals("/")) {
            return 2;
        }
        return 0;
    }
    
    private Node buildTree(List<String> tokens) {
        Stack<String> ops = new Stack<>();
        Stack<Node> nodes = new Stack<>();
        
        for (String token : tokens) {
            if (Character.isDigit(token.charAt(0))) {
                nodes.push(new Node(token.charAt(0)));
            } else if (token.equals("(")) {
                ops.push(token);
            } else if (token.equals(")")) {
                while (!ops.isEmpty() && !ops.peek().equals("(")) {
                    String op = ops.pop();
                    Node right = nodes.pop();
                    Node left = nodes.pop();
                    nodes.push(new Node(op.charAt(0), left, right));
                }
                ops.pop();
            } else {
                while (!ops.isEmpty() && !ops.peek().equals("(") && getPriority(ops.peek()) >= getPriority(token)) {
                    String op = ops.pop();
                    Node right = nodes.pop();
                    Node left = nodes.pop();
                    nodes.push(new Node(op.charAt(0), left, right));
                }
                ops.push(token);
            }
        }
        
        while (!ops.isEmpty()) {
            String op = ops.pop();
            Node right = nodes.pop();
            Node left = nodes.pop();
            nodes.push(new Node(op.charAt(0), left, right));
        }
        
        return nodes.pop();
    }
}