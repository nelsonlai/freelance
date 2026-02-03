from collections import Counter

class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        count = Counter(answers)
        result = 0
        for answer, freq in count.items():
            result += (freq + answer) // (answer + 1) * (answer + 1)
        return result
