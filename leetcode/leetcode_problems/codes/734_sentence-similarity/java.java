import java.util.*;

class Solution {
    public boolean areSentencesSimilar(String[] sentence1, String[] sentence2, List<List<String>> similarPairs) {
        if (sentence1.length != sentence2.length) {
            return false;
        }
        
        Map<String, Set<String>> similar = new HashMap<>();
        for (List<String> pair : similarPairs) {
            similar.computeIfAbsent(pair.get(0), k -> new HashSet<>()).add(pair.get(1));
            similar.computeIfAbsent(pair.get(1), k -> new HashSet<>()).add(pair.get(0));
        }
        
        for (int i = 0; i < sentence1.length; i++) {
            if (!sentence1[i].equals(sentence2[i]) && 
                !similar.getOrDefault(sentence1[i], Collections.emptySet()).contains(sentence2[i])) {
                return false;
            }
        }
        
        return true;
    }
}
