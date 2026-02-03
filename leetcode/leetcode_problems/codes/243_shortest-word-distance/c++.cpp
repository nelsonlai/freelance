/*
 * Problem: Shortest Word Distance
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        int index1 = -1;
        int index2 = -1;
        int minDistance = INT_MAX;
        
        for (int i = 0; i < wordsDict.size(); i++) {
            if (wordsDict[i] == word1) {
                index1 = i;
                if (index2 != -1) {
                    minDistance = min(minDistance, abs(index1 - index2));
                }
            } else if (wordsDict[i] == word2) {
                index2 = i;
                if (index1 != -1) {
                    minDistance = min(minDistance, abs(index1 - index2));
                }
            }
        }
        
        return minDistance;
    }
};