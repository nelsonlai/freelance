/*
 * Problem: Most Visited Sector in  a Circular Track
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        vector<int> counts(n + 1, 0);
        
        for (int i = 0; i < rounds.size() - 1; i++) {
            int start = rounds[i];
            int end = rounds[i + 1];
            
            if (start <= end) {
                for (int j = start; j <= end; j++) {
                    counts[j]++;
                }
            } else {
                for (int j = start; j <= n; j++) {
                    counts[j]++;
                }
                for (int j = 1; j <= end; j++) {
                    counts[j]++;
                }
            }
        }
        
        int maxCount = *max_element(counts.begin() + 1, counts.end());
        vector<int> result;
        for (int i = 1; i <= n; i++) {
            if (counts[i] == maxCount) {
                result.push_back(i);
            }
        }
        return result;
    }
};