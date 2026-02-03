"""
Problem: Design Excel Sum Formula
Difficulty: Hard
Tags: array, string, graph, hash, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

import re

class Excel:
    def __init__(self, height: int, width: str):
        self.height = height
        self.width = ord(width) - ord('A') + 1
        self.cells = {}
        self.formulas = {}

    def set(self, row: int, column: str, val: int) -> None:
        key = (row, column)
        self.cells[key] = val
        if key in self.formulas:
            del self.formulas[key]

    def get(self, row: int, column: str) -> int:
        key = (row, column)
        if key in self.formulas:
            return self._calculate_sum(self.formulas[key])
        return self.cells.get(key, 0)

    def sum(self, row: int, column: str, numbers: List[str]) -> int:
        key = (row, column)
        self.formulas[key] = numbers
        return self._calculate_sum(numbers)

    def _calculate_sum(self, numbers: List[str]) -> int:
        total = 0
        for num in numbers:
            if ':' in num:
                total += self._sum_range(num)
            else:
                total += self._get_cell_value(num)
        return total

    def _sum_range(self, range_str: str) -> int:
        start, end = range_str.split(':')
        start_row, start_col = self._parse_cell(start)
        end_row, end_col = self._parse_cell(end)
        total = 0
        for r in range(start_row, end_row + 1):
            for c in range(start_col, end_col + 1):
                col_char = chr(ord('A') + c - 1)
                total += self.get(r, col_char)
        return total

    def _get_cell_value(self, cell: str) -> int:
        row, col = self._parse_cell(cell)
        col_char = chr(ord('A') + col - 1)
        return self.get(row, col_char)

    def _parse_cell(self, cell: str) -> tuple:
        match = re.match(r'([A-Z]+)(\d+)', cell)
        col_str = match.group(1)
        row = int(match.group(2))
        col = 0
        for c in col_str:
            col = col * 26 + (ord(c) - ord('A') + 1)
        return (row, col)