import java.util.*;

class Solution {
    public int[] fairCandySwap(int[] aliceSizes, int[] bobSizes) {
        int sumA = 0, sumB = 0;
        for (int size : aliceSizes) {
            sumA += size;
        }
        for (int size : bobSizes) {
            sumB += size;
        }
        
        int diff = (sumB - sumA) / 2;
        Set<Integer> setB = new HashSet<>();
        for (int size : bobSizes) {
            setB.add(size);
        }
        
        for (int a : aliceSizes) {
            if (setB.contains(a + diff)) {
                return new int[]{a, a + diff};
            }
        }
        
        return new int[0];
    }
}
