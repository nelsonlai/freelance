class Solution:
    def splitIntoFibonacci(self, num: str) -> List[int]:
        n = len(num)
        
        for i in range(1, min(11, n)):
            for j in range(i + 1, min(i + 11, n)):
                first = num[:i]
                second = num[i:j]
                
                if (first.startswith('0') and len(first) > 1) or (second.startswith('0') and len(second) > 1):
                    continue
                
                result = [int(first), int(second)]
                k = j
                
                while k < n:
                    nextVal = result[-1] + result[-2]
                    nextStr = str(nextVal)
                    if nextVal > 2**31 - 1 or not num[k:].startswith(nextStr):
                        break
                    result.append(nextVal)
                    k += len(nextStr)
                
                if k == n and len(result) >= 3:
                    return result
        
        return []
