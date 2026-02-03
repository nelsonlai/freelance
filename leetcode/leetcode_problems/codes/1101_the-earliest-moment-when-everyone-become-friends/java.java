/**
 * Problem: The Earliest Moment When Everyone Become Friends
 * Difficulty: Medium
 * Tags: array, graph, sort
 * 
 * Approach: Union-Find - sort logs by time, union friends until all connected
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for Union-Find
 */
import java.util.Arrays;

class Solution {
    private int[] parent;
    
    private int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    private boolean union(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return false;
        }
        parent[px] = py;
        return true;
    }
    
    public int earliestAcq(int[][] logs, int n) {
        Arrays.sort(logs, (a, b) -> Integer.compare(a[0], b[0]));
        parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        int components = n;
        for (int[] log : logs) {
            int time = log[0];
            int x = log[1];
            int y = log[2];
            if (union(x, y)) {
                components--;
                if (components == 1) {
                    return time;
                }
            }
        }
        
        return -1;
    }
}