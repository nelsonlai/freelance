#include <string>
#include <stack>

using namespace std;

class Solution {
private:
    string build(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '#') {
                if (!st.empty()) {
                    st.pop();
                }
            } else {
                st.push(c);
            }
        }
        string result = "";
        while (!st.empty()) {
            result = st.top() + result;
            st.pop();
        }
        return result;
    }

public:
    bool backspaceCompare(string s, string t) {
        return build(s) == build(t);
    }
};
