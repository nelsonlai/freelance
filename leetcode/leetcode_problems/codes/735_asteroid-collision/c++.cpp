#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        for (int asteroid : asteroids) {
            while (!st.empty() && asteroid < 0 && st.top() > 0) {
                if (st.top() < -asteroid) {
                    st.pop();
                    continue;
                } else if (st.top() == -asteroid) {
                    st.pop();
                }
                asteroid = 0;
                break;
            }
            if (asteroid != 0) {
                st.push(asteroid);
            }
        }
        
        vector<int> result(st.size());
        for (int i = result.size() - 1; i >= 0; i--) {
            result[i] = st.top();
            st.pop();
        }
        return result;
    }
};
