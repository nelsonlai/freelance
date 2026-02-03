from collections import defaultdict

class FreqStack:
    def __init__(self):
        self.freq = defaultdict(int)
        self.group = defaultdict(list)
        self.maxFreq = 0

    def push(self, val: int) -> None:
        self.freq[val] += 1
        f = self.freq[val]
        self.maxFreq = max(self.maxFreq, f)
        self.group[f].append(val)

    def pop(self) -> int:
        x = self.group[self.maxFreq].pop()
        self.freq[x] -= 1
        if not self.group[self.maxFreq]:
            self.maxFreq -= 1
        return x
