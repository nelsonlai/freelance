/**
 * Problem: Solve the Equation
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String solveEquation(String equation) {
        String[] parts = equation.split("=");
        int[] left = parseSide(parts[0]);
        int[] right = parseSide(parts[1]);
        
        int coeff = left[0] - right[0];
        int constant = right[1] - left[1];
        
        if (coeff == 0) {
            return constant == 0 ? "Infinite solutions" : "No solution";
        }
        
        return "x=" + (constant / coeff);
    }
    
    private int[] parseSide(String side) {
        int coeff = 0, constant = 0;
        side = side.replace("+", " +").replace("-", " -");
        if (side.charAt(0) != '-' && side.charAt(0) != '+') {
            side = "+" + side;
        }
        
        String[] tokens = side.split(" ");
        for (String token : tokens) {
            if (token.isEmpty()) continue;
            
            if (token.contains("x")) {
                String num = token.replace("x", "").replace("+", "").replace("-", "");
                int val = num.isEmpty() ? 1 : Integer.parseInt(num);
                if (token.charAt(0) == '-') {
                    coeff -= val;
                } else {
                    coeff += val;
                }
            } else {
                int val = Integer.parseInt(token);
                if (token.charAt(0) == '-') {
                    constant -= val;
                } else {
                    constant += val;
                }
            }
        }
        
        return new int[]{coeff, constant};
    }
}