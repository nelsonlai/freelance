"""
Problem: Kth Smallest Product of Two Sorted Arrays
Difficulty: Hard
Tags: array, sort, search, binary search

Approach: Binary search on answer, count products <= mid
Time Complexity: O(n * m * log(max_product)) where n, m are array lengths
Space Complexity: O(1)
"""

class Solution:
    def kthSmallestProduct(self, nums1: List[int], nums2: List[int], k: int) -> int:
        def count_products(mid):
            """Count number of products <= mid"""
            count = 0
            for num1 in nums1:
                if num1 == 0:
                    if mid >= 0:
                        count += len(nums2)
                elif num1 > 0:
                    # num1 * num2 <= mid => num2 <= mid / num1
                    target = mid // num1
                    if mid < 0 and mid % num1 != 0:
                        target -= 1
                    # Count nums2 <= target
                    import bisect
                    count += bisect.bisect_right(nums2, target)
                else:  # num1 < 0
                    # num1 * num2 <= mid => num2 >= mid / num1 (reverse)
                    target = mid // num1
                    if mid < 0 and mid % num1 != 0:
                        target += 1
                    # Count nums2 >= target
                    import bisect
                    count += len(nums2) - bisect.bisect_left(nums2, target)
            return count
        
        # Binary search on answer
        left = -10**10
        right = 10**10
        
        while left < right:
            mid = (left + right) // 2
            if count_products(mid) >= k:
                right = mid
            else:
                left = mid + 1
        
        return left