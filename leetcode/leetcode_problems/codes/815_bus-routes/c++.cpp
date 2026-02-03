#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) {
            return 0;
        }
        
        unordered_map<int, vector<int>> stopToRoutes;
        for (int i = 0; i < routes.size(); i++) {
            for (int stop : routes[i]) {
                stopToRoutes[stop].push_back(i);
            }
        }
        
        queue<int> q;
        q.push(source);
        unordered_set<int> visited;
        int buses = 0;
        
        while (!q.empty()) {
            buses++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int stop = q.front();
                q.pop();
                for (int routeIdx : stopToRoutes[stop]) {
                    if (visited.find(routeIdx) != visited.end()) {
                        continue;
                    }
                    visited.insert(routeIdx);
                    for (int nextStop : routes[routeIdx]) {
                        if (nextStop == target) {
                            return buses;
                        }
                        q.push(nextStop);
                    }
                }
            }
        }
        
        return -1;
    }
};
