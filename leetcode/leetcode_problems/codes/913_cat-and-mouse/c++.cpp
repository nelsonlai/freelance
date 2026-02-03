#include <vector>
#include <cstring>

using namespace std;

class Solution {
private:
    int memo[200][50][50];
    
public:
    int catMouseGame(vector<vector<int>>& graph) {
        memset(memo, -1, sizeof(memo));
        return dfs(graph, 1, 2, 0);
    }
    
private:
    int dfs(vector<vector<int>>& graph, int mouse, int cat, int turn) {
        if (turn == 2 * graph.size()) {
            return 0;
        }
        if (mouse == 0) {
            return 1;
        }
        if (mouse == cat) {
            return 2;
        }
        if (memo[turn][mouse][cat] != -1) {
            return memo[turn][mouse][cat];
        }
        
        if (turn % 2 == 0) {
            bool canDraw = false;
            for (int next : graph[mouse]) {
                int result = dfs(graph, next, cat, turn + 1);
                if (result == 1) {
                    return memo[turn][mouse][cat] = 1;
                }
                if (result == 0) {
                    canDraw = true;
                }
            }
            return memo[turn][mouse][cat] = canDraw ? 0 : 2;
        } else {
            bool canDraw = false;
            for (int next : graph[cat]) {
                if (next == 0) continue;
                int result = dfs(graph, mouse, next, turn + 1);
                if (result == 2) {
                    return memo[turn][mouse][cat] = 2;
                }
                if (result == 0) {
                    canDraw = true;
                }
            }
            return memo[turn][mouse][cat] = canDraw ? 0 : 1;
        }
    }
};
