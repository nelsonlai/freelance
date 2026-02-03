#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        priority_queue<vector<double>, vector<vector<double>>, greater<vector<double>>> heap;
        int n = arr.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                heap.push({arr[i] * 1.0 / arr[j], (double)arr[i], (double)arr[j]});
            }
        }
        
        for (int i = 0; i < k - 1; i++) {
            heap.pop();
        }
        
        auto result = heap.top();
        return {(int)result[1], (int)result[2]};
    }
};
