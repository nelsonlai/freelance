"""
Problem: Longest Common Subpath
Difficulty: Hard
Tags: array, hash, search, rolling hash, binary search

Approach: Binary search on length, use rolling hash to check if subpath exists in all paths
Time Complexity: O(m * L * log(min_path_length)) where m is paths, L is avg path length
Space Complexity: O(L)
"""

class Solution:
    def longestCommonSubpath(self, n: int, paths: List[List[int]]) -> int:
        MOD1, MOD2 = 10**9 + 7, 10**9 + 9
        BASE1, BASE2 = 100001, 100003
        
        def check(length):
            if length == 0:
                return True
            
            # Get hash sets for first path
            hash_set = set()
            hash1, hash2 = 0, 0
            pow1, pow2 = 1, 1
            
            for i in range(len(paths[0])):
                hash1 = (hash1 * BASE1 + paths[0][i]) % MOD1
                hash2 = (hash2 * BASE2 + paths[0][i]) % MOD2
                
                if i >= length - 1:
                    if i >= length:
                        hash1 = (hash1 - paths[0][i - length] * pow1) % MOD1
                        hash2 = (hash2 - paths[0][i - length] * pow2) % MOD2
                        hash1 = (hash1 + MOD1) % MOD1
                        hash2 = (hash2 + MOD2) % MOD2
                    
                    hash_set.add((hash1, hash2))
            
            # Check other paths
            for path in paths[1:]:
                temp_set = set()
                hash1, hash2 = 0, 0
                pow1, pow2 = 1, 1
                
                for i in range(len(path)):
                    hash1 = (hash1 * BASE1 + path[i]) % MOD1
                    hash2 = (hash2 * BASE2 + path[i]) % MOD2
                    
                    if i >= length - 1:
                        if i >= length:
                            hash1 = (hash1 - path[i - length] * pow1) % MOD1
                            hash2 = (hash2 - path[i - length] * pow2) % MOD2
                            hash1 = (hash1 + MOD1) % MOD1
                            hash2 = (hash2 + MOD2) % MOD2
                        
                        if (hash1, hash2) in hash_set:
                            temp_set.add((hash1, hash2))
                
                if not temp_set:
                    return False
                hash_set = temp_set
            
            return True
        
        min_len = min(len(path) for path in paths)
        left, right = 0, min_len
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if check(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result