#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<string> obstaclesSet;
        for (auto& ob : obstacles) {
            obstaclesSet.insert(to_string(ob[0]) + "," + to_string(ob[1]));
        }
        
        int x = 0, y = 0;
        int dx = 0, dy = 1;
        int result = 0;
        
        for (int cmd : commands) {
            if (cmd == -2) {
                int temp = dx;
                dx = -dy;
                dy = temp;
            } else if (cmd == -1) {
                int temp = dx;
                dx = dy;
                dy = -temp;
            } else {
                for (int i = 0; i < cmd; i++) {
                    string next = to_string(x + dx) + "," + to_string(y + dy);
                    if (obstaclesSet.find(next) == obstaclesSet.end()) {
                        x += dx;
                        y += dy;
                        result = max(result, x * x + y * y);
                    } else {
                        break;
                    }
                }
            }
        }
        return result;
    }
};
