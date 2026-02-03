import java.util.*;

class Solution {
    public int expressiveWords(String s, String[] words) {
        List<int[]> sGroups = getGroups(s);
        int result = 0;
        
        for (String word : words) {
            List<int[]> wGroups = getGroups(word);
            if (sGroups.size() != wGroups.size()) {
                continue;
            }
            boolean valid = true;
            for (int i = 0; i < sGroups.size(); i++) {
                int[] sGroup = sGroups.get(i);
                int[] wGroup = wGroups.get(i);
                if (sGroup[0] != wGroup[0]) {
                    valid = false;
                    break;
                }
                if (sGroup[1] < wGroup[1] || (sGroup[1] < 3 && sGroup[1] != wGroup[1])) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                result++;
            }
        }
        return result;
    }
    
    private List<int[]> getGroups(String word) {
        List<int[]> groups = new ArrayList<>();
        int i = 0;
        while (i < word.length()) {
            int j = i;
            while (j < word.length() && word.charAt(j) == word.charAt(i)) {
                j++;
            }
            groups.add(new int[]{word.charAt(i), j - i});
            i = j;
        }
        return groups;
    }
}
