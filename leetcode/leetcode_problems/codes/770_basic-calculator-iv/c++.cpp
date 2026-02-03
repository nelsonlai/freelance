#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map<string, int> evaluate(string expr, unordered_map<string, int>& evalMap) {
        stack<map<string, int>> st;
        stack<int> signs;
        st.push(map<string, int>());
        signs.push(1);
        
        int i = 0;
        while (i < expr.length()) {
            char c = expr[i];
            if (c == '(') {
                i++;
                st.push(map<string, int>());
                signs.push(1);
            } else if (c == ')') {
                i++;
                auto top = st.top();
                st.pop();
                int sign = signs.top();
                signs.pop();
                auto& combine = st.top();
                for (auto& entry : top) {
                    combine[entry.first] += sign * entry.second;
                }
            } else if (c == '+' || c == '-') {
                signs.top() = (c == '+') ? 1 : -1;
                i++;
            } else {
                auto term = parseTerm(expr, i, evalMap);
                i = term["__index__"];
                multiplyTerm(term, expr, i, evalMap);
                i = term["__index__"];
                auto& combine = st.top();
                int sign = signs.top();
                for (auto& entry : term) {
                    if (entry.first != "__index__") {
                        combine[entry.first] += sign * entry.second;
                    }
                }
            }
        }
        return mapToUnordered(st.top());
    }
    
    map<string, int> parseTerm(string& expr, int& i, unordered_map<string, int>& evalMap) {
        map<string, int> term;
        if (i < expr.length() && isdigit(expr[i])) {
            int num = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            term[""] = num;
        } else {
            string var = "";
            while (i < expr.length() && isalnum(expr[i])) {
                var += expr[i];
                i++;
            }
            if (evalMap.find(var) != evalMap.end()) {
                term[""] = evalMap[var];
            } else {
                term[var] = 1;
            }
        }
        term["__index__"] = i;
        return term;
    }
    
    void multiplyTerm(map<string, int>& term, string& expr, int& i, unordered_map<string, int>& evalMap) {
        while (i < expr.length() && expr[i] == '*') {
            i++;
            auto factor = parseTerm(expr, i, evalMap);
            i = factor["__index__"];
            map<string, int> newTerm;
            for (auto& e1 : term) {
                if (e1.first == "__index__") continue;
                for (auto& e2 : factor) {
                    if (e2.first == "__index__") continue;
                    vector<string> parts;
                    if (!e1.first.empty()) parts.push_back(e1.first);
                    if (!e2.first.empty()) parts.push_back(e2.first);
                    sort(parts.begin(), parts.end());
                    string key = "";
                    for (int j = 0; j < parts.size(); j++) {
                        if (j > 0) key += "*";
                        key += parts[j];
                    }
                    newTerm[key] += e1.second * e2.second;
                }
            }
            term = newTerm;
        }
        term["__index__"] = i;
    }
    
    unordered_map<string, int> mapToUnordered(map<string, int>& m) {
        unordered_map<string, int> result;
        for (auto& entry : m) {
            result[entry.first] = entry.second;
        }
        return result;
    }
    
    vector<string> format(unordered_map<string, int>& poly) {
        vector<pair<string, int>> entries;
        for (auto& entry : poly) {
            entries.push_back({entry.first, entry.second});
        }
        sort(entries.begin(), entries.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            int aCount = count(a.first.begin(), a.first.end(), '*') + (a.first.empty() ? 0 : 1);
            int bCount = count(b.first.begin(), b.first.end(), '*') + (b.first.empty() ? 0 : 1);
            if (aCount != bCount) return aCount > bCount;
            return a.first < b.first;
        });
        
        vector<string> result;
        for (auto& entry : entries) {
            if (entry.second == 0) continue;
            if (entry.first.empty()) {
                result.push_back(to_string(entry.second));
            } else {
                if (entry.second == 1) {
                    result.push_back(entry.first);
                } else {
                    result.push_back(to_string(entry.second) + "*" + entry.first);
                }
            }
        }
        return result;
    }

public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        unordered_map<string, int> evalMap;
        for (int i = 0; i < evalvars.size(); i++) {
            evalMap[evalvars[i]] = evalints[i];
        }
        
        string expr = expression;
        expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
        auto poly = evaluate(expr, evalMap);
        return format(poly);
    }
};
