/*
 * Problem: The Score of Students Solving Math Expression
 * Difficulty: Hard
 * Tags: array, string, dp, math, hash, stack
 * 
 * Approach: DP to compute all possible results, then score based on correct/incorrect
 * Time Complexity: O(n^3) where n is length of expression
 * Space Complexity: O(n^2)
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map<string, unordered_set<int>> memo;
    
    unordered_set<int> dp(string& s, int i, int j) {
        string key = to_string(i) + "," + to_string(j);
        if (memo.count(key)) {
            return memo[key];
        }
        
        unordered_set<int> results;
        
        if (i == j) {
            results.insert(s[i] - '0');
            memo[key] = results;
            return results;
        }
        
        for (int k = i + 1; k < j; k += 2) {  // Operators are at odd indices
            unordered_set<int> left = dp(s, i, k - 1);
            unordered_set<int> right = dp(s, k + 1, j);
            char op = s[k];
            
            for (int l : left) {
                for (int r : right) {
                    int val;
                    if (op == '+') {
                        val = l + r;
                    } else {  // op == '*'
                        val = l * r;
                    }
                    if (val <= 1000) {  // Constraint: answers <= 1000
                        results.insert(val);
                    }
                }
            }
        }
        
        memo[key] = results;
        return results;
    }
    
    int evaluate(string& s) {
        // Evaluate expression correctly (multiplication before addition)
        stack<int> st;
        int num = 0;
        char op = '+';
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            
            if (!isdigit(c) || i == s.length() - 1) {
                if (op == '+') {
                    st.push(num);
                } else if (op == '*') {
                    int top = st.top();
                    st.pop();
                    st.push(top * num);
                }
                op = c;
                num = 0;
            }
        }
        
        int result = 0;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        return result;
    }
    
public:
    int scoreOfStudents(string s, vector<int>& answers) {
        // Calculate correct answer
        int correct = evaluate(s);
        
        // Use DP to find all possible results
        unordered_set<int> allResults = dp(s, 0, s.length() - 1);
        
        // Score answers
        int score = 0;
        for (int ans : answers) {
            if (ans == correct) {
                score += 5;
            } else if (allResults.count(ans)) {
                score += 2;
            }
        }
        
        return score;
    }
};