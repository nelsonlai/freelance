import random

class Solution:

    def __init__(self, n: int, blacklist: List[int]):
        self.n = n
        self.blacklist = set(blacklist)
        self.whitelist = []
        self.m = n - len(blacklist)
        
        if len(blacklist) < n // 2:
            self.whitelist = [i for i in range(n) if i not in self.blacklist]
        else:
            self.mapping = {}
            j = self.m
            for num in blacklist:
                if num < self.m:
                    while j in self.blacklist:
                        j += 1
                    self.mapping[num] = j
                    j += 1

    def pick(self) -> int:
        if len(self.blacklist) < self.n // 2:
            return random.choice(self.whitelist)
        else:
            r = random.randint(0, self.m - 1)
            return self.mapping.get(r, r)
