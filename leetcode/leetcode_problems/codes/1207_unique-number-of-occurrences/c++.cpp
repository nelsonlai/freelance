/*
 * Problem: Unique Number of Occurrences
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Count frequencies, check if all frequencies are unique
 * Time Complexity: O(n) where n is the length of arr
 * Space Complexity: O(n) for frequency map
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freq;
        for (int num : arr) {
            freq[num]++;
        }
        
        unordered_set<int> occurrences;
        for (auto& [num, count] : freq) {
            if (occurrences.count(count)) {
                return false;
            }
            occurrences.insert(count);
        }
        
        return true;
    }
};