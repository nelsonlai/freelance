/**
 * Problem: Find Latest Group of Size M
 * Difficulty: Medium
 * Tags: array, string, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int findLatestStep(int[] arr, int m) {
        int n = arr.length;
        int[] parent = new int[n + 1];
        int[] size = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
        int countM = 0;
        int result = -1;
        
        for (int step = 1; step <= n; step++) {
            int pos = arr[step - 1];
            size[pos] = 1;
            if (m == 1) {
                countM++;
            }
            
            if (pos > 1 && size[pos - 1] > 0) {
                countM = union(parent, size, pos, pos - 1, m, countM);
            }
            if (pos < n && size[pos + 1] > 0) {
                countM = union(parent, size, pos, pos + 1, m, countM);
            }
            
            if (countM > 0) {
                result = step;
            }
        }
        
        return result;
    }
    
    private int find(int[] parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    private int union(int[] parent, int[] size, int x, int y, int m, int countM) {
        int px = find(parent, x);
        int py = find(parent, y);
        if (px == py) {
            return countM;
        }
        
        if (size[px] == m) countM--;
        if (size[py] == m) countM--;
        
        if (size[px] < size[py]) {
            int temp = px;
            px = py;
            py = temp;
        }
        
        parent[py] = px;
        size[px] += size[py];
        
        if (size[px] == m) countM++;
        
        return countM;
    }
}