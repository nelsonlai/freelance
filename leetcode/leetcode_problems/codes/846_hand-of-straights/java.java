import java.util.*;

class Solution {
    public boolean isNStraightHand(int[] hand, int groupSize) {
        if (hand.length % groupSize != 0) {
            return false;
        }
        
        Map<Integer, Integer> count = new TreeMap<>();
        for (int card : hand) {
            count.put(card, count.getOrDefault(card, 0) + 1);
        }
        
        for (int key : count.keySet()) {
            if (count.get(key) > 0) {
                int need = count.get(key);
                for (int i = 0; i < groupSize; i++) {
                    if (count.getOrDefault(key + i, 0) < need) {
                        return false;
                    }
                    count.put(key + i, count.get(key + i) - need);
                }
            }
        }
        return true;
    }
}
