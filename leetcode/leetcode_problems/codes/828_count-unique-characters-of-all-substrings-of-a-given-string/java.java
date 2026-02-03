import java.util.*;

class Solution {
    public int uniqueLetterString(String s) {
        Map<Character, List<Integer>> index = new HashMap<>();
        for (char c = 'A'; c <= 'Z'; c++) {
            index.put(c, new ArrayList<>(Arrays.asList(-1, -1)));
        }
        
        int result = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            List<Integer> list = index.get(c);
            int k = list.get(0), j = list.get(1);
            result += (i - j) * (j - k);
            list.set(0, j);
            list.set(1, i);
        }
        
        for (char c = 'A'; c <= 'Z'; c++) {
            List<Integer> list = index.get(c);
            int k = list.get(0), j = list.get(1);
            result += (s.length() - j) * (j - k);
        }
        
        return result;
    }
}
