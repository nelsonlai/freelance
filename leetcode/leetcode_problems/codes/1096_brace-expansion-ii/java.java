/**
 * Problem: Brace Expansion II
 * Difficulty: Hard
 * Tags: string, hash, sort, search, stack
 * 
 * Approach: Parse expression recursively, handle union and concatenation
 * Time Complexity: O(n * m) where n is options, m is length
 * Space Complexity: O(n * m) for results
 */

import java.util.*;

class Solution {
    public List<String> braceExpansionII(String expression) {
        Set<String> result = parse(expression);
        List<String> sorted = new ArrayList<>(result);
        Collections.sort(sorted);
        return sorted;
    }
    
    private Set<String> parse(String s) {
        if (s.isEmpty()) {
            return new HashSet<>(Arrays.asList(""));
        }
        
        if (!s.contains("{")) {
            return new HashSet<>(Arrays.asList(s));
        }
        
        Set<String> result = new HashSet<>();
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
                Set<String> innerOptions = parse(inner);
                
                if (result.isEmpty()) {
                    result = innerOptions;
                } else {
                    Set<String> newResult = new HashSet<>();
                    for (String a : result) {
                        for (String b : innerOptions) {
                            newResult.add(a + b);
                        }
                    }
                    result = newResult;
                }
                
                i = j;
            } else {
                int j = i;
                while (j < s.length() && s.charAt(j) != '{' && s.charAt(j) != '}') {
                    j++;
                }
                
                String prefix = s.substring(i, j);
                if (result.isEmpty()) {
                    result.add(prefix);
                } else {
                    Set<String> newResult = new HashSet<>();
                    for (String a : result) {
                        newResult.add(a + prefix);
                    }
                    result = newResult;
                }
                
                i = j;
                
                if (i < s.length() && s.charAt(i) == ',') {
                    Set<String> rest = parse(s.substring(i + 1));
                    result.addAll(rest);
                    break;
                }
            }
        }
        
        return result;
    }
}