import java.util.*;

class Solution {
    public int[] advantageCount(int[] nums1, int[] nums2) {
        int n = nums1.length;
        Arrays.sort(nums1);
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        Arrays.sort(indices, (a, b) -> Integer.compare(nums2[a], nums2[b]));
        
        int[] result = new int[n];
        int left = 0, right = n - 1;
        
        for (int num : nums1) {
            if (num > nums2[indices[left]]) {
                result[indices[left]] = num;
                left++;
            } else {
                result[indices[right]] = num;
                right--;
            }
        }
        
        return result;
    }
}
