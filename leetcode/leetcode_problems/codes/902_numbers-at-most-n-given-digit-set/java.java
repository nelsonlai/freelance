import java.util.*;

class Solution {
    public int atMostNGivenDigitSet(String[] digits, int n) {
        String s = String.valueOf(n);
        int k = s.length();
        int[] dp = new int[k + 1];
        dp[k] = 1;
        
        for (int i = k - 1; i >= 0; i--) {
            int si = s.charAt(i) - '0';
            for (String d : digits) {
                int digit = Integer.parseInt(d);
                if (digit < si) {
                    dp[i] += Math.pow(digits.length, k - i - 1);
                } else if (digit == si) {
                    dp[i] += dp[i + 1];
                }
            }
        }
        
        int result = dp[0];
        for (int i = 1; i < k; i++) {
            result += Math.pow(digits.length, i);
        }
        return result;
    }
}
