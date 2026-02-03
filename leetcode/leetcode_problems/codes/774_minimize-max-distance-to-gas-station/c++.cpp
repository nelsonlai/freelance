#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    bool possible(vector<int>& stations, int k, double D) {
        int count = 0;
        for (int i = 0; i < stations.size() - 1; i++) {
            count += (int)((stations[i + 1] - stations[i]) / D);
        }
        return count <= k;
    }

public:
    double minmaxGasDist(vector<int>& stations, int k) {
        double left = 0, right = stations[stations.size() - 1] - stations[0];
        while (right - left > 1e-6) {
            double mid = (left + right) / 2.0;
            if (possible(stations, k, mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }
};
