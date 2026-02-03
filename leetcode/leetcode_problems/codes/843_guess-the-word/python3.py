from collections import Counter

class Solution:
    def findSecretWord(self, wordlist: List[str], master: 'Master') -> None:
        def match(a, b):
            return sum(i == j for i, j in zip(a, b))
        
        matches = 0
        while matches < 6:
            guess = Counter(wordlist).most_common(1)[0][0]
            matches = master.guess(guess)
            wordlist = [w for w in wordlist if match(guess, w) == matches]
