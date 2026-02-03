#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size();
        int result = 0;
        int i = 1;
        
        while (i < n) {
            while (i < n && arr[i-1] >= arr[i]) {
                i++;
            }
            int start = i - 1;
            
            while (i < n && arr[i-1] < arr[i]) {
                i++;
            }
            int peak = i - 1;
            
            while (i < n && arr[i-1] > arr[i]) {
                i++;
            }
            int end = i - 1;
            
            if (peak > start && end > peak) {
                result = max(result, end - start + 1);
            }
        }
        
        return result;
    }
};
