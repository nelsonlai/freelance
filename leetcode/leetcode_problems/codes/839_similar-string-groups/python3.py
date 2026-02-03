class Solution:
    def numSimilarGroups(self, strs: List[str]) -> int:
        n = len(strs)
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            parent[find(x)] = find(y)
        
        def similar(a, b):
            diff = sum(1 for i in range(len(a)) if a[i] != b[i])
            return diff == 0 or diff == 2
        
        for i in range(n):
            for j in range(i + 1, n):
                if similar(strs[i], strs[j]):
                    union(i, j)
        
        return len(set(find(i) for i in range(n)))
