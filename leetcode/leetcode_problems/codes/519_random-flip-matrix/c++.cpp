/*
 * Problem: Random Flip Matrix
 * Difficulty: Medium
 * Tags: math, hash
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>
#include <random>

using namespace std;

class Solution {
private:
    int m, n, total;
    unordered_set<int> flipped;
    mt19937 gen;
    uniform_int_distribution<int> dis;

public:
    Solution(int m, int n) : m(m), n(n), total(m * n), gen(random_device{}()) {
    }
    
    vector<int> flip() {
        uniform_int_distribution<int> dis(0, total - 1);
        while (true) {
            int idx = dis(gen);
            if (flipped.find(idx) == flipped.end()) {
                flipped.insert(idx);
                return {idx / n, idx % n};
            }
        }
    }
    
    void reset() {
        flipped.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */