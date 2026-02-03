import java.util.*;

class Solution {
    public int threeSumMulti(int[] arr, int target) {
        int MOD = 1000000007;
        Map<Integer, Long> count = new HashMap<>();
        for (int num : arr) {
            count.put(num, count.getOrDefault(num, 0L) + 1);
        }
        
        List<Integer> keys = new ArrayList<>(count.keySet());
        Collections.sort(keys);
        long result = 0;
        
        for (int i = 0; i < keys.size(); i++) {
            int x = keys.get(i);
            for (int j = i; j < keys.size(); j++) {
                int y = keys.get(j);
                int z = target - x - y;
                if (z < y) break;
                if (!count.containsKey(z)) continue;
                
                if (x == y && y == z) {
                    long cnt = count.get(x);
                    result += cnt * (cnt - 1) * (cnt - 2) / 6;
                } else if (x == y) {
                    long cnt = count.get(x);
                    result += cnt * (cnt - 1) / 2 * count.get(z);
                } else if (y == z) {
                    result += count.get(x) * count.get(y) * (count.get(y) - 1) / 2;
                } else {
                    result += count.get(x) * count.get(y) * count.get(z);
                }
            }
        }
        
        return (int)(result % MOD);
    }
}
