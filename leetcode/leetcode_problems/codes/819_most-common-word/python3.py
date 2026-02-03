import re
from collections import Counter

class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        bannedSet = set(banned)
        words = re.findall(r'\w+', paragraph.lower())
        count = Counter(word for word in words if word not in bannedSet)
        return count.most_common(1)[0][0]
