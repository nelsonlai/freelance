class Solution:
    def advantageCount(self, nums1: List[int], nums2: List[int]) -> List[int]:
        n = len(nums1)
        nums1.sort()
        indices = sorted(range(n), key=lambda i: nums2[i])
        
        result = [0] * n
        left, right = 0, n - 1
        
        for num in nums1:
            if num > nums2[indices[left]]:
                result[indices[left]] = num
                left += 1
            else:
                result[indices[right]] = num
                right -= 1
        
        return result
