class Solution:
    def splitArraySameAverage(self, nums: List[int]) -> bool:
        n = len(nums)
        total = sum(nums)
        
        possible = False
        for i in range(1, n // 2 + 1):
            if total * i % n == 0:
                possible = True
                break
        if not possible:
            return False
        
        sums = [set() for _ in range(n // 2 + 1)]
        sums[0].add(0)
        
        for num in nums:
            for i in range(len(sums) - 2, -1, -1):
                for s in sums[i]:
                    sums[i + 1].add(s + num)
        
        for i in range(1, n // 2 + 1):
            if total * i % n == 0:
                target = total * i // n
                if target in sums[i]:
                    return True
        return False
