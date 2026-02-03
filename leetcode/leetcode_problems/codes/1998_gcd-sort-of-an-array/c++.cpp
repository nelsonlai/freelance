/*
 * Problem: GCD Sort of an Array
 * Difficulty: Hard
 * Tags: array, graph, math, sort, Union-Find
 * 
 * Approach: Union-Find to connect numbers with common factors, check if can sort
 * Time Complexity: O(n * sqrt(max(nums)) + n log n)
 * Space Complexity: O(max(nums))
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    class UnionFind {
    private:
        vector<int> parent;
        
    public:
        UnionFind(int n) : parent(n) {
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unionSet(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px != py) {
                parent[px] = py;
            }
        }
    };
    
public:
    bool gcdSort(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        UnionFind uf(maxNum + 1);
        
        // Union numbers with common factors
        for (int num : nums) {
            for (int factor = 2; factor * factor <= num; factor++) {
                if (num % factor == 0) {
                    uf.unionSet(num, factor);
                    uf.unionSet(num, num / factor);
                }
            }
        }
        
        // Check if sorted array can be achieved
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());
        
        for (int i = 0; i < nums.size(); i++) {
            if (uf.find(nums[i]) != uf.find(sortedNums[i])) {
                return false;
            }
        }
        
        return true;
    }
};
