/**
 * Problem: Throne Inheritance
 * Difficulty: Medium
 * Tags: string, tree, hash, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class ThroneInheritance {
    private String king;
    private Map<String, List<String>> children;
    private Set<String> dead;

    public ThroneInheritance(String kingName) {
        this.king = kingName;
        this.children = new HashMap<>();
        this.dead = new HashSet<>();
    }
    
    public void birth(String parentName, String childName) {
        children.computeIfAbsent(parentName, k -> new ArrayList<>()).add(childName);
    }
    
    public void death(String name) {
        dead.add(name);
    }
    
    public List<String> getInheritanceOrder() {
        List<String> result = new ArrayList<>();
        dfs(king, result);
        return result;
    }
    
    private void dfs(String name, List<String> result) {
        if (!dead.contains(name)) {
            result.add(name);
        }
        if (children.containsKey(name)) {
            for (String child : children.get(name)) {
                dfs(child, result);
            }
        }
    }
}

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance obj = new ThroneInheritance(kingName);
 * obj.birth(parentName,childName);
 * obj.death(name);
 * List<String> param_3 = obj.getInheritanceOrder();
 */