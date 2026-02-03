class Solution {
    private static final int MOD = 1000000007;
    
    public int nthMagicalNumber(int n, int a, int b) {
        int L = a * b / gcd(a, b);
        long left = 0, right = (long)n * Math.min(a, b);
        
        while (left < right) {
            long mid = (left + right) / 2;
            if (mid / a + mid / b - mid / L < n) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return (int)(left % MOD);
    }
    
    private int gcd(int x, int y) {
        while (y != 0) {
            int temp = y;
            y = x % y;
            x = temp;
        }
        return x;
    }
}
