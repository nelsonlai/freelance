/**
 * Problem: The Score of Students Solving Math Expression
 * Difficulty: Hard
 * Tags: array, string, dp, math, hash, stack
 * 
 * Approach: DP to compute all possible results, then score based on correct/incorrect
 * Time Complexity: O(n^3) where n is length of expression
 * Space Complexity: O(n^2)
 */

import java.util.*;

class Solution {
    private Map<String, Set<Integer>> memo = new HashMap<>();
    
    public int scoreOfStudents(String s, int[] answers) {
        // Calculate correct answer
        int correct = evaluate(s);
        
        // Use DP to find all possible results
        Set<Integer> allResults = dp(s, 0, s.length() - 1);
        
        // Score answers
        int score = 0;
        for (int ans : answers) {
            if (ans == correct) {
                score += 5;
            } else if (allResults.contains(ans)) {
                score += 2;
            }
        }
        
        return score;
    }
    
    private Set<Integer> dp(String s, int i, int j) {
        String key = i + "," + j;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        Set<Integer> results = new HashSet<>();
        
        if (i == j) {
            results.add(s.charAt(i) - '0');
            memo.put(key, results);
            return results;
        }
        
        for (int k = i + 1; k < j; k += 2) {  // Operators are at odd indices
            Set<Integer> left = dp(s, i, k - 1);
            Set<Integer> right = dp(s, k + 1, j);
            char op = s.charAt(k);
            
            for (int l : left) {
                for (int r : right) {
                    int val;
                    if (op == '+') {
                        val = l + r;
                    } else {  // op == '*'
                        val = l * r;
                    }
                    if (val <= 1000) {  // Constraint: answers <= 1000
                        results.add(val);
                    }
                }
            }
        }
        
        memo.put(key, results);
        return results;
    }
    
    private int evaluate(String s) {
        // Evaluate expression correctly (multiplication before addition)
        Stack<Integer> stack = new Stack<>();
        int num = 0;
        char op = '+';
        
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (Character.isDigit(c)) {
                num = num * 10 + (c - '0');
            }
            
            if (!Character.isDigit(c) || i == s.length() - 1) {
                if (op == '+') {
                    stack.push(num);
                } else if (op == '*') {
                    stack.push(stack.pop() * num);
                }
                op = c;
                num = 0;
            }
        }
        
        int result = 0;
        while (!stack.isEmpty()) {
            result += stack.pop();
        }
        return result;
    }
}