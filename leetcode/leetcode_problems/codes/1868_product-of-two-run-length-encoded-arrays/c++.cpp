/*
 * Problem: Product of Two Run-Length Encoded Arrays
 * Difficulty: Medium
 * Tags: array, two pointers
 * 
 * Approach: Two pointers to process both encoded arrays, merge consecutive same values
 * Time Complexity: O(n + m) where n, m are encoded lengths
 * Space Complexity: O(1) excluding output
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        vector<vector<int>> result;
        int i = 0, j = 0;
        
        while (i < encoded1.size() && j < encoded2.size()) {
            int val1 = encoded1[i][0];
            int count1 = encoded1[i][1];
            int val2 = encoded2[j][0];
            int count2 = encoded2[j][1];
            
            int product = val1 * val2;
            int minCount = min(count1, count2);
            
            if (!result.empty() && result.back()[0] == product) {
                result.back()[1] += minCount;
            } else {
                result.push_back({product, minCount});
            }
            
            encoded1[i][1] -= minCount;
            encoded2[j][1] -= minCount;
            
            if (encoded1[i][1] == 0) i++;
            if (encoded2[j][1] == 0) j++;
        }
        
        return result;
    }
};