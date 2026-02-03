/**
 * Problem: Minimum Cost to Change the Final Value of Expression
 * Difficulty: Hard
 * Tags: string, tree, dp, math, stack
 * 
 * Approach: Parse expression tree, DP to track min cost to flip value
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int minOperationsToFlip(String expression) {
        List<Character> ops = new ArrayList<>();
        Deque<Character> stack = new ArrayDeque<>();
        
        for (char c : expression.toCharArray()) {
            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    ops.add(stack.pop());
                }
                stack.pop();
            } else if (c == '&' || c == '|') {
                while (!stack.isEmpty() && (stack.peek() == '&' || stack.peek() == '|')) {
                    ops.add(stack.pop());
                }
                stack.push(c);
            } else {
                ops.add(c);
            }
        }
        
        while (!stack.isEmpty()) {
            ops.add(stack.pop());
        }
        
        Deque<int[]> evalStack = new ArrayDeque<>();
        
        for (char op : ops) {
            if (op == '&') {
                int[] b = evalStack.pop();
                int[] a = evalStack.pop();
                if (a[0] == 1 && b[0] == 1) {
                    evalStack.push(new int[]{1, Math.min(a[1], b[1]) + 1});
                } else if (a[0] == 0 && b[0] == 0) {
                    evalStack.push(new int[]{0, Math.min(a[1], b[1]) + 1});
                } else {
                    evalStack.push(new int[]{0, 1});
                }
            } else if (op == '|') {
                int[] b = evalStack.pop();
                int[] a = evalStack.pop();
                if (a[0] == 1 && b[0] == 1) {
                    evalStack.push(new int[]{1, 1});
                } else if (a[0] == 0 && b[0] == 0) {
                    evalStack.push(new int[]{0, Math.min(a[1], b[1]) + 1});
                } else {
                    evalStack.push(new int[]{1, Math.min(a[1], b[1]) + 1});
                }
            } else {
                int val = op - '0';
                evalStack.push(new int[]{val, 1});
            }
        }
        
        return evalStack.peek()[1];
    }
}