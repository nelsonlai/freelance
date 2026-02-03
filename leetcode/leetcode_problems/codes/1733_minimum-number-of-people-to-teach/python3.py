"""
Problem: Minimum Number of People to Teach
Difficulty: Medium
Tags: array, greedy, hash

Approach: Find people who can't communicate, find language that covers most of them
Time Complexity: O(f * l + p) where f is friendships, l is languages, p is people
Space Complexity: O(p * l)
"""

class Solution:
    def minimumTeachings(self, n: int, languages: List[List[int]], friendships: List[List[int]]) -> int:
        lang_sets = [set(langs) for langs in languages]
        
        # Find people who can't communicate
        need_teaching = set()
        for u, v in friendships:
            u -= 1
            v -= 1
            if not lang_sets[u] & lang_sets[v]:
                need_teaching.add(u)
                need_teaching.add(v)
        
        if not need_teaching:
            return 0
        
        # Find language that most people already know
        lang_count = [0] * (n + 1)
        for person in need_teaching:
            for lang in lang_sets[person]:
                lang_count[lang] += 1
        
        max_known = max(lang_count) if lang_count else 0
        return len(need_teaching) - max_known