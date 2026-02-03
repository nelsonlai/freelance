import java.util.*;

class Solution {
    private Map<Integer, Integer> memo = new HashMap<>();
    
    public int racecar(int target) {
        return dp(target);
    }
    
    private int dp(int t) {
        if (memo.containsKey(t)) {
            return memo.get(t);
        }
        
        int n = 32 - Integer.numberOfLeadingZeros(t);
        if (t == (1 << n) - 1) {
            memo.put(t, n);
            return n;
        }
        
        int result = n + 1 + dp((1 << n) - 1 - t);
        for (int m = 0; m < n - 1; m++) {
            result = Math.min(result, n + m + 1 + dp(t - (1 << (n - 1)) + (1 << m)));
        }
        memo.put(t, result);
        return result;
    }
}
