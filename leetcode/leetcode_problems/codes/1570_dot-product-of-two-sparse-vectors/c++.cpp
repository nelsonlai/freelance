/*
 * Problem: Dot Product of Two Sparse Vectors
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <vector>

using namespace std;

class SparseVector {
private:
    unordered_map<int, int> nonZero;

public:
    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nonZero[i] = nums[i];
            }
        }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int result = 0;
        for (auto& [idx, val] : nonZero) {
            if (vec.nonZero.find(idx) != vec.nonZero.end()) {
                result += val * vec.nonZero[idx];
            }
        }
        return result;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);