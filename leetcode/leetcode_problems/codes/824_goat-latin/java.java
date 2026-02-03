import java.util.*;

class Solution {
    public String toGoatLatin(String sentence) {
        Set<Character> vowels = new HashSet<>(Arrays.asList('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'));
        String[] words = sentence.split(" ");
        StringBuilder result = new StringBuilder();
        
        for (int i = 0; i < words.length; i++) {
            String word = words[i];
            String newWord;
            if (vowels.contains(word.charAt(0))) {
                newWord = word + "ma";
            } else {
                newWord = word.substring(1) + word.charAt(0) + "ma";
            }
            newWord += "a".repeat(i + 1);
            if (i > 0) {
                result.append(" ");
            }
            result.append(newWord);
        }
        
        return result.toString();
    }
}
