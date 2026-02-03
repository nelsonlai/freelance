import java.util.*;

class Solution {
    public boolean splitArraySameAverage(int[] nums) {
        int n = nums.length;
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        
        boolean possible = false;
        for (int i = 1; i <= n / 2; i++) {
            if (total * i % n == 0) {
                possible = true;
                break;
            }
        }
        if (!possible) {
            return false;
        }
        
        Set<Integer>[] sums = new Set[n / 2 + 1];
        for (int i = 0; i < sums.length; i++) {
            sums[i] = new HashSet<>();
        }
        sums[0].add(0);
        
        for (int num : nums) {
            for (int i = sums.length - 2; i >= 0; i--) {
                for (int s : sums[i]) {
                    sums[i + 1].add(s + num);
                }
            }
        }
        
        for (int i = 1; i <= n / 2; i++) {
            if (total * i % n == 0) {
                int target = total * i / n;
                if (sums[i].contains(target)) {
                    return true;
                }
            }
        }
        return false;
    }
}
