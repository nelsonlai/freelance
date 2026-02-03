/*
 * Problem: Flatten 2D Vector
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Vector2D {
private:
    vector<vector<int>> vec;
    int row;
    int col;
    
    void advance() {
        while (row < vec.size() && col >= vec[row].size()) {
            row++;
            col = 0;
        }
    }

public:
    Vector2D(vector<vector<int>>& vec) {
        this->vec = vec;
        this->row = 0;
        this->col = 0;
        advance();
    }
    
    int next() {
        int result = vec[row][col];
        col++;
        advance();
        return result;
    }
    
    bool hasNext() {
        return row < vec.size();
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */