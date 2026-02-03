/*
 * Problem: Random Pick with Weight
 * Difficulty: Medium
 * Tags: array, math, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> prefixSum;
    int total;
    mt19937 gen;
    uniform_int_distribution<int> dis;

public:
    Solution(vector<int>& w) : gen(random_device{}()) {
        int sum = 0;
        for (int weight : w) {
            sum += weight;
            prefixSum.push_back(sum);
        }
        total = sum;
    }
    
    int pickIndex() {
        uniform_int_distribution<int> dis(1, total);
        int target = dis(gen);
        
        return lower_bound(prefixSum.begin(), prefixSum.end(), target) - prefixSum.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */