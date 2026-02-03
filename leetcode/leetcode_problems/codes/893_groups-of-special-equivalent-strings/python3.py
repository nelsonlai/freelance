class Solution:
    def numSpecialEquivGroups(self, words: List[str]) -> int:
        def signature(word):
            even = sorted(word[::2])
            odd = sorted(word[1::2])
            return tuple(even + odd)
        
        return len(set(signature(word) for word in words))
