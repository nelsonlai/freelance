/**
 * Problem: Implement Magic Dictionary
 * Difficulty: Medium
 * Tags: array, string, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class MagicDictionary {
    private Set<String> words;
    private Map<String, Integer> count;

    public MagicDictionary() {
        words = new HashSet<>();
        count = new HashMap<>();
    }
    
    public void buildDict(String[] dictionary) {
        words = new HashSet<>(Arrays.asList(dictionary));
        count = new HashMap<>();
        
        for (String word : dictionary) {
            for (int i = 0; i < word.length(); i++) {
                String pattern = word.substring(0, i) + "*" + word.substring(i + 1);
                count.put(pattern, count.getOrDefault(pattern, 0) + 1);
            }
        }
    }
    
    public boolean search(String searchWord) {
        for (int i = 0; i < searchWord.length(); i++) {
            String pattern = searchWord.substring(0, i) + "*" + searchWord.substring(i + 1);
            if (count.containsKey(pattern)) {
                if (!words.contains(searchWord) || count.get(pattern) > 1) {
                    return true;
                }
            }
        }
        return false;
    }
}

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dictionary);
 * boolean param_2 = obj.search(searchWord);
 */