/*
 * Problem: Least Number of Unique Integers after K Removals
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        for (int num : arr) {
            freq[num]++;
        }
        
        vector<int> sortedFreq;
        for (auto& [num, count] : freq) {
            sortedFreq.push_back(count);
        }
        sort(sortedFreq.begin(), sortedFreq.end());
        
        int removed = 0;
        for (int count : sortedFreq) {
            if (k >= count) {
                k -= count;
                removed++;
            } else {
                break;
            }
        }
        
        return sortedFreq.size() - removed;
    }
};