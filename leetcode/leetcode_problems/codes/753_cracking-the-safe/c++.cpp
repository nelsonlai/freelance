#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set<string> visited;
    string result;
    int k;
    
    void dfs(string node) {
        for (int x = 0; x < k; x++) {
            string neighbor = node + to_string(x);
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                dfs(neighbor.substr(1));
                result += to_string(x);
            }
        }
    }

public:
    string crackSafe(int n, int k) {
        this->k = k;
        string start(n - 1, '0');
        dfs(start);
        return result + start;
    }
};
