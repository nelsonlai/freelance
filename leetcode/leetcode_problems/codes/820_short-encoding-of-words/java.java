import java.util.*;

class Solution {
    public int minimumLengthEncoding(String[] words) {
        String[] reversed = new String[words.length];
        for (int i = 0; i < words.length; i++) {
            reversed[i] = new StringBuilder(words[i]).reverse().toString();
        }
        Arrays.sort(reversed);
        
        int result = 0;
        for (int i = 0; i < reversed.length; i++) {
            if (i + 1 < reversed.length && reversed[i + 1].startsWith(reversed[i])) {
                continue;
            }
            result += reversed[i].length() + 1;
        }
        return result;
    }
}
