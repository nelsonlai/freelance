import java.util.*;

class Solution {
    public int maxProfitAssignment(int[] difficulty, int[] profit, int[] worker) {
        int n = difficulty.length;
        int[][] jobs = new int[n][2];
        for (int i = 0; i < n; i++) {
            jobs[i] = new int[]{difficulty[i], profit[i]};
        }
        Arrays.sort(jobs, (a, b) -> a[0] - b[0]);
        Arrays.sort(worker);
        
        int result = 0;
        int i = 0;
        int best = 0;
        
        for (int ability : worker) {
            while (i < n && jobs[i][0] <= ability) {
                best = Math.max(best, jobs[i][1]);
                i++;
            }
            result += best;
        }
        return result;
    }
}
