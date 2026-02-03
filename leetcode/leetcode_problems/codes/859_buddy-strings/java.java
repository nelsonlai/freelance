import java.util.*;

class Solution {
    public boolean buddyStrings(String s, String goal) {
        if (s.length() != goal.length()) {
            return false;
        }
        
        if (s.equals(goal)) {
            Set<Character> set = new HashSet<>();
            for (char c : s.toCharArray()) {
                set.add(c);
            }
            return set.size() < s.length();
        }
        
        List<int[]> diff = new ArrayList<>();
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) != goal.charAt(i)) {
                diff.add(new int[]{s.charAt(i), goal.charAt(i)});
            }
        }
        return diff.size() == 2 && diff.get(0)[0] == diff.get(1)[1] && diff.get(0)[1] == diff.get(1)[0];
    }
}
