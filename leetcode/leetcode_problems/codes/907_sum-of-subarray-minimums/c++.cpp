#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int MOD = 1000000007;
        stack<int> st;
        long result = 0;
        
        for (int i = 0; i <= arr.size(); i++) {
            while (!st.empty() && (i == arr.size() || arr[st.top()] >= arr[i])) {
                int mid = st.top();
                st.pop();
                int left = st.empty() ? -1 : st.top();
                int right = i;
                result = (result + (long)arr[mid] * (mid - left) * (right - mid)) % MOD;
            }
            st.push(i);
        }
        
        return (int)result;
    }
};
