"""
Problem: Search Suggestions System
Difficulty: Medium
Tags: array, string, graph, sort, search, queue, heap

Approach: Sort products, use binary search to find matching prefix, return top 3
Time Complexity: O(n log n + m * log n) where n is products, m is searchWord length
Space Complexity: O(1) excluding result
"""

import bisect

class Solution:
    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        products.sort()
        result = []
        prefix = ""
        
        for char in searchWord:
            prefix += char
            idx = bisect.bisect_left(products, prefix)
            suggestions = []
            for i in range(idx, min(idx + 3, len(products))):
                if products[i].startswith(prefix):
                    suggestions.append(products[i])
                else:
                    break
            result.append(suggestions)
        
        return result