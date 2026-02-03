#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size();
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; i++) {
            jobs.push_back({difficulty[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        sort(worker.begin(), worker.end());
        
        int result = 0;
        int i = 0;
        int best = 0;
        
        for (int ability : worker) {
            while (i < n && jobs[i].first <= ability) {
                best = max(best, jobs[i].second);
                i++;
            }
            result += best;
        }
        return result;
    }
};
