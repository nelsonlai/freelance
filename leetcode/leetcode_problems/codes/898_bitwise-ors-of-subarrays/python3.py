class Solution:
    def subarrayBitwiseORs(self, arr: List[int]) -> int:
        result = set()
        cur = {0}
        
        for x in arr:
            cur = {x | y for y in cur} | {x}
            result |= cur
        
        return len(result)
