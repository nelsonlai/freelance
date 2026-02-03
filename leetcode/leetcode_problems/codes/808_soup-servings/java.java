import java.util.*;

class Solution {
    private Map<String, Double> memo = new HashMap<>();
    
    public double soupServings(int n) {
        if (n > 4800) {
            return 1.0;
        }
        return dp(n, n);
    }
    
    private double dp(int a, int b) {
        if (a <= 0 && b <= 0) {
            return 0.5;
        }
        if (a <= 0) {
            return 1.0;
        }
        if (b <= 0) {
            return 0.0;
        }
        String key = a + "," + b;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        double result = 0.25 * (dp(a-100, b) + dp(a-75, b-25) + dp(a-50, b-50) + dp(a-25, b-75));
        memo.put(key, result);
        return result;
    }
}
