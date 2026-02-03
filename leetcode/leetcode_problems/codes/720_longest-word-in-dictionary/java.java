import java.util.*;

class Solution {
    public String longestWord(String[] words) {
        Arrays.sort(words);
        Set<String> wordSet = new HashSet<>();
        for (String word : words) {
            wordSet.add(word);
        }
        
        String result = "";
        for (String word : words) {
            if (word.length() > result.length() || 
                (word.length() == result.length() && word.compareTo(result) < 0)) {
                boolean valid = true;
                for (int i = 1; i < word.length(); i++) {
                    if (!wordSet.contains(word.substring(0, i))) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    result = word;
                }
            }
        }
        
        return result;
    }
}
