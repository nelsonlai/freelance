/**
 * Problem: Shortest Word Distance II
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class WordDistance {
    private Map<String, List<Integer>> wordIndices;

    public WordDistance(String[] wordsDict) {
        wordIndices = new HashMap<>();
        for (int i = 0; i < wordsDict.length; i++) {
            wordIndices.putIfAbsent(wordsDict[i], new ArrayList<>());
            wordIndices.get(wordsDict[i]).add(i);
        }
    }
    
    public int shortest(String word1, String word2) {
        List<Integer> indices1 = wordIndices.get(word1);
        List<Integer> indices2 = wordIndices.get(word2);
        
        int i = 0, j = 0;
        int minDistance = Integer.MAX_VALUE;
        
        while (i < indices1.size() && j < indices2.size()) {
            minDistance = Math.min(minDistance, Math.abs(indices1.get(i) - indices2.get(j)));
            if (indices1.get(i) < indices2.get(j)) {
                i++;
            } else {
                j++;
            }
        }
        
        return minDistance;
    }
}

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(wordsDict);
 * int param_1 = obj.shortest(word1,word2);
 */