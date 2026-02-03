import java.util.*;

class Solution {
    public int largestOverlap(int[][] img1, int[][] img2) {
        int n = img1.length;
        List<int[]> A = new ArrayList<>();
        List<int[]> B = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 1) {
                    A.add(new int[]{i, j});
                }
                if (img2[i][j] == 1) {
                    B.add(new int[]{i, j});
                }
            }
        }
        
        Map<String, Integer> count = new HashMap<>();
        for (int[] a : A) {
            for (int[] b : B) {
                String key = (a[0] - b[0]) + "," + (a[1] - b[1]);
                count.put(key, count.getOrDefault(key, 0) + 1);
            }
        }
        
        return count.values().stream().mapToInt(Integer::intValue).max().orElse(0);
    }
}
