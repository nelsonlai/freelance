/*
 * Problem: Build Binary Expression Tree From Infix Expression
 * Difficulty: Hard
 * Tags: string, tree, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
    int getPriority(char op) {
        if (op == '+' || op == '-') {
            return 1;
        }
        if (op == '*' || op == '/') {
            return 2;
        }
        return 0;
    }
    
    vector<string> tokenize(string s) {
        vector<string> tokens;
        int i = 0;
        while (i < s.length()) {
            if (isdigit(s[i])) {
                string num;
                while (i < s.length() && isdigit(s[i])) {
                    num += s[i];
                    i++;
                }
                tokens.push_back(num);
            } else {
                tokens.push_back(string(1, s[i]));
                i++;
            }
        }
        return tokens;
    }
    
    Node* buildTree(vector<string>& tokens) {
        stack<char> ops;
        stack<Node*> nodes;
        
        for (string& token : tokens) {
            if (isdigit(token[0])) {
                nodes.push(new Node(token[0]));
            } else if (token == "(") {
                ops.push('(');
            } else if (token == ")") {
                while (!ops.empty() && ops.top() != '(') {
                    char op = ops.top();
                    ops.pop();
                    Node* right = nodes.top();
                    nodes.pop();
                    Node* left = nodes.top();
                    nodes.pop();
                    nodes.push(new Node(op, left, right));
                }
                ops.pop();
            } else {
                char op = token[0];
                while (!ops.empty() && ops.top() != '(' && getPriority(ops.top()) >= getPriority(op)) {
                    char topOp = ops.top();
                    ops.pop();
                    Node* right = nodes.top();
                    nodes.pop();
                    Node* left = nodes.top();
                    nodes.pop();
                    nodes.push(new Node(topOp, left, right));
                }
                ops.push(op);
            }
        }
        
        while (!ops.empty()) {
            char op = ops.top();
            ops.pop();
            Node* right = nodes.top();
            nodes.pop();
            Node* left = nodes.top();
            nodes.pop();
            nodes.push(new Node(op, left, right));
        }
        
        return nodes.top();
    }
    
public:
    Node* expTree(string s) {
        vector<string> tokens = tokenize(s);
        return buildTree(tokens);
    }
};