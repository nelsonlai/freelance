import java.util.*;

class Solution {
    public int intersectionSizeTwo(int[][] intervals) {
        Arrays.sort(intervals, (a, b) -> a[1] != b[1] ? a[1] - b[1] : b[0] - a[0]);
        List<Integer> result = new ArrayList<>();
        
        for (int[] interval : intervals) {
            int start = interval[0], end = interval[1];
            int count = 0;
            for (int x : result) {
                if (start <= x && x <= end) {
                    count++;
                }
            }
            if (count == 0) {
                result.add(end - 1);
                result.add(end);
            } else if (count == 1) {
                result.add(end);
            }
        }
        
        return result.size();
    }
}
