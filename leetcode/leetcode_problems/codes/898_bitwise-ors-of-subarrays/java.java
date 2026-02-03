import java.util.*;

class Solution {
    public int subarrayBitwiseORs(int[] arr) {
        Set<Integer> result = new HashSet<>();
        Set<Integer> cur = new HashSet<>();
        cur.add(0);
        
        for (int x : arr) {
            Set<Integer> next = new HashSet<>();
            for (int y : cur) {
                next.add(x | y);
            }
            next.add(x);
            cur = next;
            result.addAll(cur);
        }
        
        return result.size();
    }
}
