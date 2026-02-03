"""
Problem: People Whose List of Favorite Companies Is Not a Subset of Another List
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Convert to sets, check if each list is subset of any other
Time Complexity: O(n^2 * m) where n is people, m is companies
Space Complexity: O(n * m) for sets
"""

class Solution:
    def peopleIndexes(self, favoriteCompanies: List[List[str]]) -> List[int]:
        sets = [set(companies) for companies in favoriteCompanies]
        result = []
        
        for i in range(len(sets)):
            is_subset = False
            for j in range(len(sets)):
                if i != j and sets[i].issubset(sets[j]):
                    is_subset = True
                    break
            if not is_subset:
                result.append(i)
        
        return result