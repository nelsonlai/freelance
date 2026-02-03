import java.util.*;

class Solution {
    public List<List<Integer>> largeGroupPositions(String s) {
        List<List<Integer>> result = new ArrayList<>();
        int i = 0;
        while (i < s.length()) {
            int j = i;
            while (j < s.length() && s.charAt(j) == s.charAt(i)) {
                j++;
            }
            if (j - i >= 3) {
                result.add(Arrays.asList(i, j - 1));
            }
            i = j;
        }
        return result;
    }
}
