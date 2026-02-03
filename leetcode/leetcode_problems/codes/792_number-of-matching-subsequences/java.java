import java.util.*;

class Solution {
    public int numMatchingSubseq(String s, String[] words) {
        Map<Character, List<Iterator<Character>>> waiting = new HashMap<>();
        for (String word : words) {
            char first = word.charAt(0);
            waiting.computeIfAbsent(first, k -> new ArrayList<>()).add(new WordIterator(word));
        }
        
        int result = 0;
        for (char c : s.toCharArray()) {
            List<Iterator<Character>> old = waiting.remove(c);
            if (old != null) {
                for (Iterator<Character> it : old) {
                    if (it.hasNext()) {
                        char next = it.next();
                        waiting.computeIfAbsent(next, k -> new ArrayList<>()).add(it);
                    } else {
                        result++;
                    }
                }
            }
        }
        return result;
    }
    
    class WordIterator implements Iterator<Character> {
        private String word;
        private int index;
        
        WordIterator(String word) {
            this.word = word;
            this.index = 1;
        }
        
        @Override
        public boolean hasNext() {
            return index < word.length();
        }
        
        @Override
        public Character next() {
            return word.charAt(index++);
        }
    }
}
