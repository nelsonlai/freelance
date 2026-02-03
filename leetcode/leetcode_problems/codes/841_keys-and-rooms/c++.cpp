#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set<int> visited;
    vector<vector<int>>* rooms;
    
    void dfs(int room) {
        if (visited.find(room) != visited.end()) {
            return;
        }
        visited.insert(room);
        for (int key : (*rooms)[room]) {
            dfs(key);
        }
    }

public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        this->rooms = &rooms;
        dfs(0);
        return visited.size() == rooms.size();
    }
};
