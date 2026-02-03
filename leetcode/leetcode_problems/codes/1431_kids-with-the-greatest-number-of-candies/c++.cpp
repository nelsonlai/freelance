/*
 * Problem: Kids With the Greatest Number of Candies
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Find max, check if each kid can have max with extra candies
 * Time Complexity: O(n) where n is length of candies
 * Space Complexity: O(n) for result
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandies = *max_element(candies.begin(), candies.end());
        
        vector<bool> result;
        for (int candy : candies) {
            result.push_back(candy + extraCandies >= maxCandies);
        }
        
        return result;
    }
};