class Solution {
    public int minSwap(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int swap = 1, noSwap = 0;
        
        for (int i = 1; i < n; i++) {
            int newSwap = n, newNoSwap = n;
            if (nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1]) {
                newNoSwap = Math.min(newNoSwap, noSwap);
                newSwap = Math.min(newSwap, swap + 1);
            }
            if (nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1]) {
                newNoSwap = Math.min(newNoSwap, swap);
                newSwap = Math.min(newSwap, noSwap + 1);
            }
            swap = newSwap;
            noSwap = newNoSwap;
        }
        
        return Math.min(swap, noSwap);
    }
}
