class Solution(object):
    def getPermutation(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        nums = [str(i) for i in range(1, n + 1)]
        result = []
        k -= 1  # Convert to 0-indexed
        
        # Calculate factorials
        fact = [1] * n
        for i in range(1, n):
            fact[i] = fact[i - 1] * i
        
        for i in range(n - 1, -1, -1):
            index = k // fact[i]
            result.append(nums.pop(index))
            k %= fact[i]
        
        return ''.join(result)