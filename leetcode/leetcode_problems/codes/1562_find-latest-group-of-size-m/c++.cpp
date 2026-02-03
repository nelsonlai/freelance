/*
 * Problem: Find Latest Group of Size M
 * Difficulty: Medium
 * Tags: array, string, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>

using namespace std;

class Solution {
private:
    int find(vector<int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    int unite(vector<int>& parent, vector<int>& size, int x, int y, int m, int countM) {
        int px = find(parent, x);
        int py = find(parent, y);
        if (px == py) {
            return countM;
        }
        
        if (size[px] == m) countM--;
        if (size[py] == m) countM--;
        
        if (size[px] < size[py]) {
            swap(px, py);
        }
        
        parent[py] = px;
        size[px] += size[py];
        
        if (size[px] == m) countM++;
        
        return countM;
    }
    
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        vector<int> parent(n + 1);
        vector<int> size(n + 1, 0);
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
                countM = unite(parent, size, pos, pos - 1, m, countM);
            }
            if (pos < n && size[pos + 1] > 0) {
                countM = unite(parent, size, pos, pos + 1, m, countM);
            }
            
            if (countM > 0) {
                result = step;
            }
        }
        
        return result;
    }
};