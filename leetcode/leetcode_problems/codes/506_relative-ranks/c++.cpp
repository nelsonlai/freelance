/*
 * Problem: Relative Ranks
 * Difficulty: Easy
 * Tags: array, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<pair<int, int>> sorted;
        for (int i = 0; i < n; i++) {
            sorted.push_back({score[i], i});
        }
        sort(sorted.begin(), sorted.end(), greater<pair<int, int>>());
        
        vector<string> result(n);
        vector<string> medals = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        
        for (int rank = 0; rank < n; rank++) {
            int idx = sorted[rank].second;
            if (rank < 3) {
                result[idx] = medals[rank];
            } else {
                result[idx] = to_string(rank + 1);
            }
        }
        
        return result;
    }
};