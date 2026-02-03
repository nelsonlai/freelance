/*
 * Problem: The k Strongest Values in an Array
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        int median = arr[(arr.size() - 1) / 2];
        
        sort(arr.begin(), arr.end(), [&](int a, int b) {
            int strengthA = abs(a - median);
            int strengthB = abs(b - median);
            if (strengthA != strengthB) {
                return strengthA > strengthB;
            }
            return a > b;
        });
        
        return vector<int>(arr.begin(), arr.begin() + k);
    }
};