#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    int n;
    vector<vector<int>>* grid;
    unordered_map<string, int> memo;
    
    int dp(int r1, int c1, int r2, int c2) {
        if (r1 == n || c1 == n || r2 == n || c2 == n || (*grid)[r1][c1] == -1 || (*grid)[r2][c2] == -1) {
            return INT_MIN;
        }
        
        if (r1 == n - 1 && c1 == n - 1) {
            return (*grid)[r1][c1];
        }
        
        string key = to_string(r1) + "," + to_string(c1) + "," + to_string(r2) + "," + to_string(c2);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int result = (*grid)[r1][c1];
        if (r1 != r2 || c1 != c2) {
            result += (*grid)[r2][c2];
        }
        
        result += max({
            dp(r1 + 1, c1, r2 + 1, c2),
            dp(r1 + 1, c1, r2, c2 + 1),
            dp(r1, c1 + 1, r2 + 1, c2),
            dp(r1, c1 + 1, r2, c2 + 1)
        });
        
        memo[key] = result;
        return result;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        this->n = grid.size();
        this->grid = &grid;
        return max(0, dp(0, 0, 0, 0));
    }
};
