#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> heap;
        int i = 0;
        int result = 0;
        long fuel = startFuel;
        
        while (fuel < target) {
            while (i < stations.size() && stations[i][0] <= fuel) {
                heap.push(stations[i][1]);
                i++;
            }
            
            if (heap.empty()) {
                return -1;
            }
            
            fuel += heap.top();
            heap.pop();
            result++;
        }
        
        return result;
    }
};
