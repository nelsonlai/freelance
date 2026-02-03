/**
 * Problem: Brace Expansion
 * Difficulty: Medium
 * Tags: string, graph, sort, search, stack
 * 
 * Approach: Parse expression, generate all combinations using backtracking
 * Time Complexity: O(n * m) where n is options, m is length
 * Space Complexity: O(n * m) for results
 */

import java.util.*;

class Solution {
    public String[] expand(String s) {
        List<List<String>> options = parse(s);
        List<String> result = new ArrayList<>();
        combine(options, 0, new StringBuilder(), result);
        Collections.sort(result);
        return result.toArray(new String[0]);
    }
    
    private List<List<String>> parse(String s) {
        List<List<String>> options = new ArrayList<>();
        int i = 0;
        
        while (i < s.length()) {
            if (s.charAt(i) == '{') {
                int j = i + 1;
                int depth = 1;
                while (j < s.length() && depth > 0) {
                    if (s.charAt(j) == '{') depth++;
                    else if (s.charAt(j) == '}') depth--;
                    j++;
                }
                
                String inner = s.substring(i + 1, j - 1);
                List<String> group = new ArrayList<>();
                for (String option : inner.split(",")) {
                    group.add(option);
                }
                Collections.sort(group);
                options.add(group);
                i = j;
            } else {
                StringBuilder current = new StringBuilder();
                while (i < s.length() && s.charAt(i) != '{' && s.charAt(i) != '}') {
                    current.append(s.charAt(i));
                    i++;
                }
                if (current.length() > 0) {
                    options.add(Arrays.asList(current.toString()));
                }
            }
        }
        
        return options;
    }
    
    private void combine(List<List<String>> options, int idx, StringBuilder current, List<String> result) {
        if (idx == options.size()) {
            result.add(current.toString());
            return;
        }
        
        for (String option : options.get(idx)) {
            current.append(option);
            combine(options, idx + 1, current, result);
            current.setLength(current.length() - option.length());
        }
    }
}