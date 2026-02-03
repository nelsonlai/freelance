class Solution:
    def threeEqualParts(self, arr: List[int]) -> List[int]:
        ones = sum(arr)
        if ones % 3 != 0:
            return [-1, -1]
        if ones == 0:
            return [0, 2]
        
        target = ones // 3
        first = second = third = -1
        count = 0
        
        for i in range(len(arr)):
            if arr[i] == 1:
                if count == 0:
                    first = i
                elif count == target:
                    second = i
                elif count == 2 * target:
                    third = i
                count += 1
        
        n = len(arr)
        length = n - third
        
        if first + length <= second and second + length <= third:
            i = first + length - 1
            j = second + length
            if arr[first:first+length] == arr[second:second+length] == arr[third:]:
                return [i, j]
        
        return [-1, -1]
