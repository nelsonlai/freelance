/*
 * Problem: Lonely Pixel II
 * Difficulty: Medium
 * Tags: array, hash
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
    int findBlackPixel(vector<vector<char>>& picture, int target) {
        int m = picture.size(), n = picture[0].size();
        unordered_map<int, int> rowCount, colCount;
        unordered_map<string, int> rowPatterns;
        
        for (int i = 0; i < m; i++) {
            string pattern = "";
            for (int j = 0; j < n; j++) {
                pattern += picture[i][j];
                if (picture[i][j] == 'B') {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
            rowPatterns[pattern]++;
        }
        
        int result = 0;
        for (int j = 0; j < n; j++) {
            if (colCount[j] == target) {
                for (int i = 0; i < m; i++) {
                    if (picture[i][j] == 'B') {
                        string pattern = "";
                        for (int k = 0; k < n; k++) {
                            pattern += picture[i][k];
                        }
                        if (rowCount[i] == target && rowPatterns[pattern] == target) {
                            result += target;
                        }
                        break;
                    }
                }
            }
        }
        
        return result;
    }
};