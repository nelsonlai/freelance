/*
 * Problem: Random Point in Non-overlapping Rectangles
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
    vector<vector<int>> rects;
    vector<int> weights;
    mt19937 gen;
    uniform_int_distribution<int> dis;

public:
    Solution(vector<vector<int>>& rects) : rects(rects), gen(random_device{}()) {
        int total = 0;
        for (auto& rect : rects) {
            int area = (rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
            total += area;
            weights.push_back(total);
        }
    }
    
    vector<int> pick() {
        uniform_int_distribution<int> dis(0, weights.back() - 1);
        int target = dis(gen);
        
        int index = upper_bound(weights.begin(), weights.end(), target) - weights.begin();
        vector<int>& rect = rects[index];
        
        uniform_int_distribution<int> xDis(rect[0], rect[2]);
        uniform_int_distribution<int> yDis(rect[1], rect[3]);
        
        return {xDis(gen), yDis(gen)};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */