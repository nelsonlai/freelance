import java.util.*;

class Solution {
    public String orderlyQueue(String s, int k) {
        if (k == 1) {
            String result = s;
            for (int i = 1; i < s.length(); i++) {
                String candidate = s.substring(i) + s.substring(0, i);
                if (candidate.compareTo(result) < 0) {
                    result = candidate;
                }
            }
            return result;
        }
        char[] chars = s.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }
}
