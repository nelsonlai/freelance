class Solution {
    private int[] parent;
    
    public int numSimilarGroups(String[] strs) {
        int n = strs.length;
        parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (similar(strs[i], strs[j])) {
                    union(i, j);
                }
            }
        }
        
        Set<Integer> groups = new HashSet<>();
        for (int i = 0; i < n; i++) {
            groups.add(find(i));
        }
        return groups.size();
    }
    
    private int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    private void union(int x, int y) {
        parent[find(x)] = find(y);
    }
    
    private boolean similar(String a, String b) {
        int diff = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a.charAt(i) != b.charAt(i)) {
                diff++;
            }
        }
        return diff == 0 || diff == 2;
    }
}
