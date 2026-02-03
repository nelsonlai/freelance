#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, int>> cars;
        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }
        sort(cars.begin(), cars.end());
        
        vector<double> times(n);
        for (int i = 0; i < n; i++) {
            times[i] = (double)(target - cars[i].first) / cars[i].second;
        }
        
        int result = 0;
        double cur = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (times[i] > cur) {
                result++;
                cur = times[i];
            }
        }
        return result;
    }
};
