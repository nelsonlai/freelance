/*
 * Problem: Kill Process
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> children;
        for (int i = 0; i < ppid.size(); i++) {
            children[ppid[i]].push_back(pid[i]);
        }
        
        vector<int> result;
        stack<int> st;
        st.push(kill);
        
        while (!st.empty()) {
            int process = st.top();
            st.pop();
            result.push_back(process);
            if (children.find(process) != children.end()) {
                for (int child : children[process]) {
                    st.push(child);
                }
            }
        }
        
        return result;
    }
};