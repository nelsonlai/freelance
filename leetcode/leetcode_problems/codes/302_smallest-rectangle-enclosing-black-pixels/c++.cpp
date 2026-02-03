/*
 * Problem: Smallest Rectangle Enclosing Black Pixels
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
private:
    int searchRows(vector<vector<char>>& image, int i, int j, bool opt) {
        while (i != j) {
            int mid = (i + j) / 2;
            bool hasOne = false;
            for (int k = 0; k < image[0].size(); k++) {
                if (image[mid][k] == '1') {
                    hasOne = true;
                    break;
                }
            }
            if (hasOne == opt) {
                j = mid;
            } else {
                i = mid + 1;
            }
        }
        return i;
    }
    
    int searchCols(vector<vector<char>>& image, int i, int j, bool opt) {
        while (i != j) {
            int mid = (i + j) / 2;
            bool hasOne = false;
            for (int k = 0; k < image.size(); k++) {
                if (image[k][mid] == '1') {
                    hasOne = true;
                    break;
                }
            }
            if (hasOne == opt) {
                j = mid;
            } else {
                i = mid + 1;
            }
        }
        return i;
    }

public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size();
        int n = image[0].size();
        
        int top = searchRows(image, 0, x, true);
        int bottom = searchRows(image, x, m, false);
        int left = searchCols(image, 0, y, true);
        int right = searchCols(image, y, n, false);
        
        return (bottom - top) * (right - left);
    }
};