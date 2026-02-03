import java.util.*;

class Solution {
    private Map<String, List<Character>> rules;
    
    public boolean pyramidTransition(String bottom, List<String> allowed) {
        rules = new HashMap<>();
        for (String rule : allowed) {
            String key = rule.substring(0, 2);
            rules.computeIfAbsent(key, k -> new ArrayList<>()).add(rule.charAt(2));
        }
        return dfs(bottom);
    }
    
    private boolean dfs(String level) {
        if (level.length() == 1) {
            return true;
        }
        return buildNext(level, 0, new StringBuilder());
    }
    
    private boolean buildNext(String level, int i, StringBuilder current) {
        if (i == level.length() - 1) {
            return dfs(current.toString());
        }
        
        String key = level.substring(i, i + 2);
        if (rules.containsKey(key)) {
            for (char c : rules.get(key)) {
                current.append(c);
                if (buildNext(level, i + 1, current)) {
                    return true;
                }
                current.setLength(current.length() - 1);
            }
        }
        return false;
    }
}
