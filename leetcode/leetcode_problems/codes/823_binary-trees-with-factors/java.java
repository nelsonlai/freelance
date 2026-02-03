import java.util.*;

class Solution {
    public int numFactoredBinaryTrees(int[] arr) {
        int MOD = 1000000007;
        Arrays.sort(arr);
        Map<Integer, Long> dp = new HashMap<>();
        for (int num : arr) {
            dp.put(num, 1L);
        }
        
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] % arr[j] == 0) {
                    int factor = arr[i] / arr[j];
                    if (dp.containsKey(factor)) {
                        dp.put(arr[i], (dp.get(arr[i]) + dp.get(arr[j]) * dp.get(factor)) % MOD);
                    }
                }
            }
        }
        
        long result = 0;
        for (long val : dp.values()) {
            result = (result + val) % MOD;
        }
        return (int) result;
    }
}
