class Solution:
    def ambiguousCoordinates(self, s: str) -> List[str]:
        s = s[1:-1]
        n = len(s)
        result = []
        
        def valid(s):
            if len(s) == 1:
                return True
            if s[0] == '0' and s[-1] == '0':
                return False
            if s[0] == '0':
                return False
            if s[-1] == '0':
                return True
            return True
        
        def generate(s):
            if not valid(s):
                return []
            if len(s) == 1:
                return [s]
            result = []
            if s[0] != '0':
                result.append(s)
            for i in range(1, len(s)):
                left, right = s[:i], s[i:]
                if (left[0] != '0' or len(left) == 1) and right[-1] != '0':
                    result.append(left + '.' + right)
            return result
        
        for i in range(1, n):
            left = generate(s[:i])
            right = generate(s[i:])
            for l in left:
                for r in right:
                    result.append(f"({l}, {r})")
        
        return result
