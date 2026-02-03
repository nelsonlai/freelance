/*
 * Problem: Next Greater Element I
 * Difficulty: Easy
 * Tags: array, hash, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        unordered_map<int, int> nextGreater;
        
        for (int num : nums2) {
            while (!st.empty() && st.top() < num) {
                nextGreater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }
        
        vector<int> result;
        for (int num : nums1) {
            result.push_back(nextGreater.count(num) ? nextGreater[num] : -1);
        }
        
        return result;
    }
};