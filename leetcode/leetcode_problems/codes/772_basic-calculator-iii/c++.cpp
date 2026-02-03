#include <string>
#include <stack>
#include <cctype>

using namespace std;

class Solution {
private:
    int i;
    
    int evaluate(string& expr) {
        stack<int> st;
        int num = 0;
        char sign = '+';
        
        while (i < expr.length()) {
            char c = expr[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '(') {
                i++;
                num = evaluate(expr);
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')') {
                if (sign == '+') {
                    st.push(num);
                } else if (sign == '-') {
                    st.push(-num);
                } else if (sign == '*') {
                    int top = st.top();
                    st.pop();
                    st.push(top * num);
                } else if (sign == '/') {
                    int top = st.top();
                    st.pop();
                    st.push(top / num);
                }
                
                if (c == ')') {
                    break;
                }
                
                sign = c;
                num = 0;
            }
            i++;
        }
        
        if (sign == '+') {
            st.push(num);
        } else if (sign == '-') {
            st.push(-num);
        } else if (sign == '*') {
            int top = st.top();
            st.pop();
            st.push(top * num);
        } else if (sign == '/') {
            int top = st.top();
            st.pop();
            st.push(top / num);
        }
        
        int result = 0;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        return result;
    }

public:
    int calculate(string s) {
        i = 0;
        return evaluate(s);
    }
};
