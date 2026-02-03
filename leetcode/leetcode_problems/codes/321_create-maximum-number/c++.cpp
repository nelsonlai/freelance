/*
 * Problem: Create Maximum Number
 * Difficulty: Hard
 * Tags: array, greedy, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> getMax(vector<int>& nums, int k) {
        vector<int> result;
        int drop = nums.size() - k;
        stack<int> st;
        
        for (int num : nums) {
            while (drop > 0 && !st.empty() && st.top() < num) {
                st.pop();
                drop--;
            }
            st.push(num);
        }
        
        while (st.size() > k) {
            st.pop();
        }
        
        while (!st.empty()) {
            result.insert(result.begin(), st.top());
            st.pop();
        }
        
        return result;
    }
    
    vector<int> merge(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        int i = 0, j = 0;
        
        while (i < nums1.size() || j < nums2.size()) {
            if (i >= nums1.size()) {
                result.push_back(nums2[j++]);
            } else if (j >= nums2.size()) {
                result.push_back(nums1[i++]);
            } else if (greater(nums1, i, nums2, j)) {
                result.push_back(nums1[i++]);
            } else {
                result.push_back(nums2[j++]);
            }
        }
        
        return result;
    }
    
    bool greater(vector<int>& nums1, int i, vector<int>& nums2, int j) {
        while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
            i++;
            j++;
        }
        return j == nums2.size() || (i < nums1.size() && nums1[i] > nums2[j]);
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        vector<int> result(k, 0);
        
        for (int i = max(0, k - n); i <= min(k, m); i++) {
            vector<int> candidate = merge(getMax(nums1, i), getMax(nums2, k - i));
            if (greater(candidate, 0, result, 0)) {
                result = candidate;
            }
        }
        
        return result;
    }
};