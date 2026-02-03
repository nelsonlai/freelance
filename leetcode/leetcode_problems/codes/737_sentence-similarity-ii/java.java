import java.util.*;

class Solution {
    public boolean areSentencesSimilarTwo(String[] sentence1, String[] sentence2, List<List<String>> similarPairs) {
        if (sentence1.length != sentence2.length) {
            return false;
        }
        
        Map<String, Set<String>> graph = new HashMap<>();
        for (List<String> pair : similarPairs) {
            graph.computeIfAbsent(pair.get(0), k -> new HashSet<>()).add(pair.get(1));
            graph.computeIfAbsent(pair.get(1), k -> new HashSet<>()).add(pair.get(0));
        }
        
        for (int i = 0; i < sentence1.length; i++) {
            if (!sentence1[i].equals(sentence2[i]) && !dfs(sentence1[i], sentence2[i], graph, new HashSet<>())) {
                return false;
            }
        }
        
        return true;
    }
    
    private boolean dfs(String word1, String word2, Map<String, Set<String>> graph, Set<String> visited) {
        if (word1.equals(word2)) {
            return true;
        }
        visited.add(word1);
        for (String neighbor : graph.getOrDefault(word1, Collections.emptySet())) {
            if (!visited.contains(neighbor) && dfs(neighbor, word2, graph, visited)) {
                return true;
            }
        }
        return false;
    }
}
