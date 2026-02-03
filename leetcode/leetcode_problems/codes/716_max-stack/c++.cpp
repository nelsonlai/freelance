#include <stack>

using namespace std;

class MaxStack {
private:
    stack<int> st;
    stack<int> maxSt;

public:
    MaxStack() {
        
    }
    
    void push(int x) {
        st.push(x);
        if (maxSt.empty() || x >= maxSt.top()) {
            maxSt.push(x);
        }
    }
    
    int pop() {
        int val = st.top();
        st.pop();
        if (!maxSt.empty() && val == maxSt.top()) {
            maxSt.pop();
        }
        return val;
    }
    
    int top() {
        return st.top();
    }
    
    int peekMax() {
        return maxSt.top();
    }
    
    int popMax() {
        int maxVal = maxSt.top();
        stack<int> temp;
        while (st.top() != maxVal) {
            temp.push(pop());
        }
        pop();
        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
        return maxVal;
    }
};
