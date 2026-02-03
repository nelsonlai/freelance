import java.util.*;

class Solution {
    public int[] anagramMappings(int[] nums1, int[] nums2) {
        Map<Integer, Integer> mapping = new HashMap<>();
        for (int i = 0; i < nums2.length; i++) {
            mapping.put(nums2[i], i);
        }
        
        int[] result = new int[nums1.length];
        for (int i = 0; i < nums1.length; i++) {
            result[i] = mapping.get(nums1[i]);
        }
        return result;
    }
}
