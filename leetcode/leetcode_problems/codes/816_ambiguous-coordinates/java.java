import java.util.*;

class Solution {
    public List<String> ambiguousCoordinates(String s) {
        s = s.substring(1, s.length() - 1);
        int n = s.length();
        List<String> result = new ArrayList<>();
        
        for (int i = 1; i < n; i++) {
            List<String> left = generate(s.substring(0, i));
            List<String> right = generate(s.substring(i));
            for (String l : left) {
                for (String r : right) {
                    result.add("(" + l + ", " + r + ")");
                }
            }
        }
        return result;
    }
    
    private List<String> generate(String s) {
        List<String> result = new ArrayList<>();
        if (s.length() == 1) {
            result.add(s);
            return result;
        }
        if (s.charAt(0) != '0') {
            result.add(s);
        }
        for (int i = 1; i < s.length(); i++) {
            String left = s.substring(0, i);
            String right = s.substring(i);
            if ((left.length() == 1 || left.charAt(0) != '0') && right.charAt(right.length() - 1) != '0') {
                result.add(left + "." + right);
            }
        }
        return result;
    }
}
