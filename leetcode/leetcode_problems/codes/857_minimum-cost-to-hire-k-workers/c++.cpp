#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, double>> workers;
        for (int i = 0; i < n; i++) {
            workers.push_back({(double)wage[i] / quality[i], quality[i]});
        }
        sort(workers.begin(), workers.end());
        
        priority_queue<double> heap;
        double sumq = 0;
        double result = 1e9;
        
        for (auto& worker : workers) {
            double ratio = worker.first;
            double q = worker.second;
            heap.push(q);
            sumq += q;
            if (heap.size() > k) {
                sumq -= heap.top();
                heap.pop();
            }
            if (heap.size() == k) {
                result = min(result, ratio * sumq);
            }
        }
        return result;
    }
};
