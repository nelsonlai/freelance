import java.util.*;

class Solution {
    public List<String> basicCalculatorIV(String expression, String[] evalvars, int[] evalints) {
        Map<String, Integer> evalMap = new HashMap<>();
        for (int i = 0; i < evalvars.length; i++) {
            evalMap.put(evalvars[i], evalints[i]);
        }
        
        Map<String, Integer> poly = evaluate(expression.replaceAll(" ", ""), evalMap);
        return format(poly);
    }
    
    private Map<String, Integer> evaluate(String expr, Map<String, Integer> evalMap) {
        Map<String, Integer> result = new HashMap<>();
        Stack<Map<String, Integer>> stack = new Stack<>();
        Stack<Integer> signs = new Stack<>();
        stack.push(new HashMap<>());
        signs.push(1);
        
        int i = 0;
        while (i < expr.length()) {
            char c = expr.charAt(i);
            if (c == '(') {
                i++;
                stack.push(new HashMap<>());
                signs.push(1);
            } else if (c == ')') {
                i++;
                Map<String, Integer> top = stack.pop();
                int sign = signs.pop();
                Map<String, Integer> combine = stack.peek();
                for (Map.Entry<String, Integer> entry : top.entrySet()) {
                    combine.put(entry.getKey(), combine.getOrDefault(entry.getKey(), 0) + sign * entry.getValue());
                }
            } else if (c == '+' || c == '-') {
                signs.set(signs.size() - 1, c == '+' ? 1 : -1);
                i++;
            } else {
                Map<String, Integer> term = parseTerm(expr, i, evalMap);
                i = term.remove("__index__");
                multiplyTerm(term, expr, i, evalMap);
                i = term.remove("__index__");
                Map<String, Integer> combine = stack.peek();
                int sign = signs.peek();
                for (Map.Entry<String, Integer> entry : term.entrySet()) {
                    combine.put(entry.getKey(), combine.getOrDefault(entry.getKey(), 0) + sign * entry.getValue());
                }
            }
        }
        return stack.pop();
    }
    
    private Map<String, Integer> parseTerm(String expr, int i, Map<String, Integer> evalMap) {
        Map<String, Integer> term = new HashMap<>();
        if (i < expr.length() && Character.isDigit(expr.charAt(i))) {
            int num = 0;
            while (i < expr.length() && Character.isDigit(expr.charAt(i))) {
                num = num * 10 + (expr.charAt(i) - '0');
                i++;
            }
            term.put("", num);
        } else {
            StringBuilder var = new StringBuilder();
            while (i < expr.length() && Character.isLetterOrDigit(expr.charAt(i))) {
                var.append(expr.charAt(i));
                i++;
            }
            String varStr = var.toString();
            if (evalMap.containsKey(varStr)) {
                term.put("", evalMap.get(varStr));
            } else {
                term.put(varStr, 1);
            }
        }
        term.put("__index__", i);
        return term;
    }
    
    private void multiplyTerm(Map<String, Integer> term, String expr, int i, Map<String, Integer> evalMap) {
        while (i < expr.length() && expr.charAt(i) == '*') {
            i++;
            Map<String, Integer> factor = parseTerm(expr, i, evalMap);
            i = factor.remove("__index__");
            Map<String, Integer> newTerm = new HashMap<>();
            for (String k1 : term.keySet()) {
                for (String k2 : factor.keySet()) {
                    List<String> parts = new ArrayList<>();
                    if (!k1.isEmpty()) parts.add(k1);
                    if (!k2.isEmpty()) parts.add(k2);
                    Collections.sort(parts);
                    String key = String.join("*", parts);
                    newTerm.put(key, newTerm.getOrDefault(key, 0) + term.get(k1) * factor.get(k2));
                }
            }
            term.clear();
            term.putAll(newTerm);
        }
        term.put("__index__", i);
    }
    
    private List<String> format(Map<String, Integer> poly) {
        List<String> result = new ArrayList<>();
        List<Map.Entry<String, Integer>> entries = new ArrayList<>(poly.entrySet());
        entries.sort((a, b) -> {
            int cmp = Integer.compare(b.getKey().split("\\*").length, a.getKey().split("\\*").length);
            if (cmp != 0) return cmp;
            return a.getKey().compareTo(b.getKey());
        });
        
        for (Map.Entry<String, Integer> entry : entries) {
            if (entry.getValue() == 0) continue;
            String key = entry.getKey();
            int coeff = entry.getValue();
            if (key.isEmpty()) {
                result.add(String.valueOf(coeff));
            } else {
                result.add(coeff == 1 ? key : coeff + "*" + key);
            }
        }
        return result;
    }
}
