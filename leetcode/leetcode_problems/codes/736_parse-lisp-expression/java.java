import java.util.*;

class Solution {
    public int evaluate(String expression) {
        return parse(expression, new HashMap<>());
    }
    
    private int parse(String expr, Map<String, Integer> env) {
        if (expr.charAt(0) != '(') {
            if (Character.isDigit(expr.charAt(0)) || expr.charAt(0) == '-') {
                return Integer.parseInt(expr);
            }
            return env.get(expr);
        }
        
        expr = expr.substring(1, expr.length() - 1);
        List<String> tokens = tokenize(expr);
        
        if (tokens.get(0).equals("add")) {
            return parse(tokens.get(1), env) + parse(tokens.get(2), env);
        } else if (tokens.get(0).equals("mult")) {
            return parse(tokens.get(1), env) * parse(tokens.get(2), env);
        } else {
            Map<String, Integer> newEnv = new HashMap<>(env);
            for (int i = 1; i < tokens.size() - 1; i += 2) {
                newEnv.put(tokens.get(i), parse(tokens.get(i + 1), newEnv));
            }
            return parse(tokens.get(tokens.size() - 1), newEnv);
        }
    }
    
    private List<String> tokenize(String expr) {
        List<String> tokens = new ArrayList<>();
        int i = 0;
        while (i < expr.length()) {
            if (expr.charAt(i) == '(') {
                int count = 0;
                int j = i;
                while (j < expr.length()) {
                    if (expr.charAt(j) == '(') count++;
                    else if (expr.charAt(j) == ')') count--;
                    if (count == 0) break;
                    j++;
                }
                tokens.add(expr.substring(i, j + 1));
                i = j + 2;
            } else {
                int j = i;
                while (j < expr.length() && expr.charAt(j) != ' ') j++;
                tokens.add(expr.substring(i, j));
                i = j + 1;
            }
        }
        return tokens;
    }
}
