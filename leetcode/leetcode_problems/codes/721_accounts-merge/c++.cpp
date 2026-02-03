#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> emailToName;
        unordered_map<string, unordered_set<string>> graph;
        
        for (auto& account : accounts) {
            string name = account[0];
            for (int i = 1; i < account.size(); i++) {
                string email = account[i];
                graph[account[1]].insert(email);
                graph[email].insert(account[1]);
                emailToName[email] = name;
            }
        }
        
        unordered_set<string> visited;
        vector<vector<string>> result;
        
        for (auto& [email, neighbors] : graph) {
            if (visited.find(email) == visited.end()) {
                stack<string> st;
                st.push(email);
                visited.insert(email);
                vector<string> emails;
                while (!st.empty()) {
                    string node = st.top();
                    st.pop();
                    emails.push_back(node);
                    for (string neighbor : graph[node]) {
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            st.push(neighbor);
                        }
                    }
                }
                sort(emails.begin(), emails.end());
                emails.insert(emails.begin(), emailToName[email]);
                result.push_back(emails);
            }
        }
        
        return result;
    }
};
