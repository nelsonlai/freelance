#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> st;
        for (int num : arr) {
            if (st.empty() || num >= st.top()) {
                st.push(num);
            } else {
                int maxVal = st.top();
                st.pop();
                while (!st.empty() && num < st.top()) {
                    st.pop();
                }
                st.push(maxVal);
            }
        }
        return st.size();
    }
};
