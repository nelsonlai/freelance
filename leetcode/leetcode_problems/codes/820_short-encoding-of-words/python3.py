class Solution:
    def minimumLengthEncoding(self, words: List[str]) -> int:
        words = sorted([w[::-1] for w in words])
        result = 0
        for i in range(len(words)):
            if i + 1 < len(words) and words[i+1].startswith(words[i]):
                continue
            result += len(words[i]) + 1
        return result
