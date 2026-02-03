/*
 * Problem: Queue Reconstruction by Height
 * Difficulty: Medium
 * Tags: array, tree, sort, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] < b[1];
            }
            return a[0] > b[0];
        });
        
        vector<vector<int>> result;
        for (auto& person : people) {
            result.insert(result.begin() + person[1], person);
        }
        
        return result;
    }
};