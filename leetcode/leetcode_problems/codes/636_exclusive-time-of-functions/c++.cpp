/*
 * Problem: Exclusive Time of Functions
 * Difficulty: Medium
 * Tags: array, string, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> result(n, 0);
        stack<int> st;
        int prevTime = 0;
        
        for (string log : logs) {
            stringstream ss(log);
            string token;
            vector<string> parts;
            while (getline(ss, token, ':')) {
                parts.push_back(token);
            }
            
            int funcId = stoi(parts[0]);
            string status = parts[1];
            int time = stoi(parts[2]);
            
            if (status == "start") {
                if (!st.empty()) {
                    result[st.top()] += time - prevTime;
                }
                st.push(funcId);
                prevTime = time;
            } else {
                result[st.top()] += time - prevTime + 1;
                st.pop();
                prevTime = time + 1;
            }
        }
        
        return result;
    }
};