class Solution {
    public int consecutiveNumbersSum(int n) {
        int result = 0;
        int k = 1;
        while (k * (k - 1) < 2 * n) {
            if ((2 * n - k * (k - 1)) % (2 * k) == 0) {
                result++;
            }
            k++;
        }
        return result;
    }
}
