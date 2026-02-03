import java.util.*;

class Solution {
    public int lenLongestFibSubseq(int[] arr) {
        Map<Integer, Integer> index = new HashMap<>();
        for (int i = 0; i < arr.length; i++) {
            index.put(arr[i], i);
        }
        
        Map<String, Integer> longest = new HashMap<>();
        int result = 0;
        
        for (int k = 0; k < arr.length; k++) {
            for (int j = 0; j < k; j++) {
                int i = index.getOrDefault(arr[k] - arr[j], -1);
                if (i >= 0 && i < j) {
                    String key = i + "," + j;
                    int cand = longest.getOrDefault(key, 2) + 1;
                    longest.put(j + "," + k, cand);
                    result = Math.max(result, cand);
                }
            }
        }
        
        return result >= 3 ? result : 0;
    }
}
