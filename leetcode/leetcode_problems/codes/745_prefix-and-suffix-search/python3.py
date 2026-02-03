class WordFilter:

    def __init__(self, words: List[str]):
        self.prefix = {}
        self.suffix = {}
        for i, word in enumerate(words):
            for j in range(len(word) + 1):
                prefix = word[:j]
                suffix = word[j:]
                if prefix not in self.prefix:
                    self.prefix[prefix] = []
                self.prefix[prefix].append(i)
                if suffix not in self.suffix:
                    self.suffix[suffix] = []
                self.suffix[suffix].append(i)

    def f(self, pref: str, suff: str) -> int:
        if pref not in self.prefix or suff not in self.suffix:
            return -1
        prefixIndices = set(self.prefix[pref])
        suffixIndices = set(self.suffix[suff])
        intersection = prefixIndices & suffixIndices
        return max(intersection) if intersection else -1
