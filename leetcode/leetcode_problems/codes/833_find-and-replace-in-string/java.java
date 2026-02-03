import java.util.*;

class Solution {
    public String findReplaceString(String s, int[] indices, String[] sources, String[] targets) {
        List<int[]> sorted = new ArrayList<>();
        for (int i = 0; i < indices.length; i++) {
            sorted.add(new int[]{indices[i], i});
        }
        sorted.sort((a, b) -> b[0] - a[0]);
        
        for (int[] item : sorted) {
            int idx = item[0];
            int i = item[1];
            if (s.substring(idx, idx + sources[i].length()).equals(sources[i])) {
                s = s.substring(0, idx) + targets[i] + s.substring(idx + sources[i].length());
            }
        }
        return s;
    }
}
