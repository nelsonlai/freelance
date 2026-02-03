import java.util.*;

class Solution {
    private List<String> result;
    
    public List<String> letterCasePermutation(String s) {
        result = new ArrayList<>();
        backtrack(s, 0, "");
        return result;
    }
    
    private void backtrack(String s, int i, String current) {
        if (i == s.length()) {
            result.add(current);
            return;
        }
        
        char c = s.charAt(i);
        if (Character.isLetter(c)) {
            backtrack(s, i + 1, current + Character.toLowerCase(c));
            backtrack(s, i + 1, current + Character.toUpperCase(c));
        } else {
            backtrack(s, i + 1, current + c);
        }
    }
}
