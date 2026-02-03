import java.util.*;

class Solution {
    public int flipgame(int[] fronts, int[] backs) {
        Set<Integer> same = new HashSet<>();
        for (int i = 0; i < fronts.length; i++) {
            if (fronts[i] == backs[i]) {
                same.add(fronts[i]);
            }
        }
        
        int result = Integer.MAX_VALUE;
        for (int i = 0; i < fronts.length; i++) {
            if (!same.contains(fronts[i])) {
                result = Math.min(result, fronts[i]);
            }
            if (!same.contains(backs[i])) {
                result = Math.min(result, backs[i]);
            }
        }
        
        return result == Integer.MAX_VALUE ? 0 : result;
    }
}
