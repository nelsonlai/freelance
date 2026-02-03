#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

using namespace std;

class Solution {
private:
    int parse(string expr, unordered_map<string, int> env) {
        if (expr[0] != '(') {
            if (isdigit(expr[0]) || expr[0] == '-') {
                return stoi(expr);
            }
            return env[expr];
        }
        
        expr = expr.substr(1, expr.length() - 2);
        vector<string> tokens = tokenize(expr);
        
        if (tokens[0] == "add") {
            return parse(tokens[1], env) + parse(tokens[2], env);
        } else if (tokens[0] == "mult") {
            return parse(tokens[1], env) * parse(tokens[2], env);
        } else {
            unordered_map<string, int> newEnv = env;
            for (int i = 1; i < tokens.size() - 1; i += 2) {
                newEnv[tokens[i]] = parse(tokens[i + 1], newEnv);
            }
            return parse(tokens[tokens.size() - 1], newEnv);
        }
    }
    
    vector<string> tokenize(string expr) {
        vector<string> tokens;
        int i = 0;
        while (i < expr.length()) {
            if (expr[i] == '(') {
                int count = 0;
                int j = i;
                while (j < expr.length()) {
                    if (expr[j] == '(') count++;
                    else if (expr[j] == ')') count--;
                    if (count == 0) break;
                    j++;
                }
                tokens.push_back(expr.substr(i, j - i + 1));
                i = j + 2;
            } else {
                int j = i;
                while (j < expr.length() && expr[j] != ' ') j++;
                tokens.push_back(expr.substr(i, j - i));
                i = j + 1;
            }
        }
        return tokens;
    }

public:
    int evaluate(string expression) {
        return parse(expression, unordered_map<string, int>());
    }
};
