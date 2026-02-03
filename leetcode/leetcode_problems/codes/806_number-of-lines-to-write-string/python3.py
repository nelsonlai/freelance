class Solution:
    def numberOfLines(self, widths: List[int], s: str) -> List[int]:
        lines = 1
        current = 0
        for c in s:
            width = widths[ord(c) - ord('a')]
            if current + width > 100:
                lines += 1
                current = width
            else:
                current += width
        return [lines, current]
