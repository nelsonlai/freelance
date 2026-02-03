#include <vector>

using namespace std;

class Solution {
private:
    int originalColor;
    int newColor;
    vector<vector<int>>* image;
    
    void dfs(int r, int c) {
        if (r < 0 || r >= (*image).size() || c < 0 || c >= (*image)[0].size() || (*image)[r][c] != originalColor) {
            return;
        }
        (*image)[r][c] = newColor;
        dfs(r + 1, c);
        dfs(r - 1, c);
        dfs(r, c + 1);
        dfs(r, c - 1);
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image[sr][sc] == color) {
            return image;
        }
        
        this->image = &image;
        this->originalColor = image[sr][sc];
        this->newColor = color;
        
        dfs(sr, sc);
        return image;
    }
};
