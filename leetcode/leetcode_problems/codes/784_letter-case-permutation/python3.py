class Solution:
    def letterCasePermutation(self, s: str) -> List[str]:
        result = []
        
        def backtrack(i, current):
            if i == len(s):
                result.append(current)
                return
            
            if s[i].isalpha():
                backtrack(i + 1, current + s[i].lower())
                backtrack(i + 1, current + s[i].upper())
            else:
                backtrack(i + 1, current + s[i])
        
        backtrack(0, "")
        return result
