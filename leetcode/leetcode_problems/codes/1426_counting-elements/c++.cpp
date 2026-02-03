/*
 * Problem: Counting Elements
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int countElements(vector<int>& arr) {
        unordered_set<int> set(arr.begin(), arr.end());
        int count = 0;
        for (int num : arr) {
            if (set.find(num + 1) != set.end()) {
                count++;
            }
        }
        return count;
    }
};