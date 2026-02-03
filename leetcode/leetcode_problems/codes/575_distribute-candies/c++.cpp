/*
 * Problem: Distribute Candies
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        unordered_set<int> uniqueTypes(candyType.begin(), candyType.end());
        int maxCandies = candyType.size() / 2;
        return min(uniqueTypes.size(), maxCandies);
    }
};