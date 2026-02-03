#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    struct Region {
        vector<pair<int, int>> infected;
        set<pair<int, int>> frontiers;
    };
    
    void dfs(vector<vector<int>>& grid, int i, int j, set<string>& visited, Region& region) {
        string key = to_string(i) + "," + to_string(j);
        if (visited.find(key) != visited.end()) return;
        visited.insert(key);
        region.infected.push_back({i, j});
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto& dir : dirs) {
            int ni = i + dir[0], nj = j + dir[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                if (grid[ni][nj] == 0) {
                    region.frontiers.insert({ni, nj});
                } else if (grid[ni][nj] == 1) {
                    dfs(grid, ni, nj, visited, region);
                }
            }
        }
    }

public:
    int containVirus(vector<vector<int>>& isInfected) {
        int m = isInfected.size(), n = isInfected[0].size();
        int result = 0;
        
        while (true) {
            vector<Region> regions;
            set<string> visited;
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (isInfected[i][j] == 1 && visited.find(to_string(i) + "," + to_string(j)) == visited.end()) {
                        Region region;
                        dfs(isInfected, i, j, visited, region);
                        if (!region.frontiers.empty()) {
                            regions.push_back(region);
                        }
                    }
                }
            }
            
            if (regions.empty()) break;
            
            sort(regions.begin(), regions.end(), [](const Region& a, const Region& b) {
                return a.frontiers.size() > b.frontiers.size();
            });
            
            Region& target = regions[0];
            for (auto& cell : target.infected) {
                isInfected[cell.first][cell.second] = 2;
            }
            
            result += target.frontiers.size();
            
            for (int idx = 1; idx < regions.size(); idx++) {
                Region& region = regions[idx];
                for (auto& cell : region.infected) {
                    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
                    for (auto& dir : dirs) {
                        int ni = cell.first + dir[0], nj = cell.second + dir[1];
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && isInfected[ni][nj] == 0) {
                            isInfected[ni][nj] = 1;
                        }
                    }
                }
            }
        }
        
        return result;
    }
};
