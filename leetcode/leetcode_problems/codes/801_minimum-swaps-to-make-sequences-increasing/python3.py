class Solution:
    def minSwap(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        swap, noSwap = 1, 0
        
        for i in range(1, n):
            newSwap = newNoSwap = n
            if nums1[i] > nums1[i-1] and nums2[i] > nums2[i-1]:
                newNoSwap = min(newNoSwap, noSwap)
                newSwap = min(newSwap, swap + 1)
            if nums1[i] > nums2[i-1] and nums2[i] > nums1[i-1]:
                newNoSwap = min(newNoSwap, swap)
                newSwap = min(newSwap, noSwap + 1)
            swap, noSwap = newSwap, newNoSwap
        
        return min(swap, noSwap)
