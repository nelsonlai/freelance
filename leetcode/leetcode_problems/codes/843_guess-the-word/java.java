import java.util.*;

class Solution {
    public void findSecretWord(String[] wordlist, Master master) {
        List<String> words = new ArrayList<>(Arrays.asList(wordlist));
        int matches = 0;
        while (matches < 6) {
            String guess = words.get(0);
            matches = master.guess(guess);
            List<String> next = new ArrayList<>();
            for (String word : words) {
                if (match(guess, word) == matches) {
                    next.add(word);
                }
            }
            words = next;
        }
    }
    
    private int match(String a, String b) {
        int count = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a.charAt(i) == b.charAt(i)) {
                count++;
            }
        }
        return count;
    }
}
