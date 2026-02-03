import java.util.*;

class Solution {
    public String shortestCompletingWord(String licensePlate, String[] words) {
        Map<Character, Integer> target = new HashMap<>();
        for (char c : licensePlate.toCharArray()) {
            if (Character.isLetter(c)) {
                char lower = Character.toLowerCase(c);
                target.put(lower, target.getOrDefault(lower, 0) + 1);
            }
        }
        
        String result = null;
        for (String word : words) {
            Map<Character, Integer> wordCount = new HashMap<>();
            for (char c : word.toCharArray()) {
                char lower = Character.toLowerCase(c);
                wordCount.put(lower, wordCount.getOrDefault(lower, 0) + 1);
            }
            
            boolean valid = true;
            for (Map.Entry<Character, Integer> entry : target.entrySet()) {
                if (wordCount.getOrDefault(entry.getKey(), 0) < entry.getValue()) {
                    valid = false;
                    break;
                }
            }
            
            if (valid && (result == null || word.length() < result.length())) {
                result = word;
            }
        }
        
        return result;
    }
}
