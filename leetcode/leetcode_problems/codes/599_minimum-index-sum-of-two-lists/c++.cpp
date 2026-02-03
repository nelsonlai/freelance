/*
 * Problem: Minimum Index Sum of Two Lists
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> indexMap;
        for (int i = 0; i < list1.size(); i++) {
            indexMap[list1[i]] = i;
        }
        
        int minSum = INT_MAX;
        vector<string> result;
        
        for (int j = 0; j < list2.size(); j++) {
            if (indexMap.find(list2[j]) != indexMap.end()) {
                int indexSum = indexMap[list2[j]] + j;
                if (indexSum < minSum) {
                    minSum = indexSum;
                    result.clear();
                    result.push_back(list2[j]);
                } else if (indexSum == minSum) {
                    result.push_back(list2[j]);
                }
            }
        }
        
        return result;
    }
};