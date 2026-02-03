import java.util.*;

class Solution {
    public int minSwapsCouples(int[] row) {
        int n = row.length;
        Map<Integer, Integer> pos = new HashMap<>();
        for (int i = 0; i < n; i++) {
            pos.put(row[i], i);
        }
        
        int swaps = 0;
        for (int i = 0; i < n; i += 2) {
            int partner = row[i] ^ 1;
            if (row[i + 1] != partner) {
                int j = pos.get(partner);
                int temp = row[i + 1];
                row[i + 1] = row[j];
                row[j] = temp;
                pos.put(row[i + 1], i + 1);
                pos.put(row[j], j);
                swaps++;
            }
        }
        
        return swaps;
    }
}
