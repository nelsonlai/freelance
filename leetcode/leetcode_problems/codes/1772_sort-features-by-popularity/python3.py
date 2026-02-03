"""
Problem: Sort Features by Popularity
Difficulty: Medium
Tags: array, string, hash, sort

Approach: Count frequency of each feature in responses, sort by frequency then original order
Time Complexity: O(n * m + k log k) where n is responses, m is words, k is features
Space Complexity: O(k)
"""

from collections import Counter

class Solution:
    def sortFeatures(self, features: List[str], responses: List[str]) -> List[str]:
        feature_set = set(features)
        freq = Counter()
        
        for response in responses:
            words = set(response.split())
            for feature in features:
                if feature in words:
                    freq[feature] += 1
        
        # Sort by frequency (descending), then by original index
        feature_index = {feature: i for i, feature in enumerate(features)}
        return sorted(features, key=lambda x: (-freq[x], feature_index[x]))