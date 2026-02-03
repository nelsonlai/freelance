/*
 * Problem: Design an Expression Tree With Evaluate Function
 * Difficulty: Medium
 * Tags: array, tree, math, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <stack>

using namespace std;

/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
    virtual ~Node() {}
    virtual int evaluate() const = 0;
protected:
    // define your fields here
};

class NumNode : public Node {
private:
    int val;
public:
    NumNode(int v) : val(v) {}
    int evaluate() const override {
        return val;
    }
};

class OpNode : public Node {
private:
    char op;
    Node* left;
    Node* right;
public:
    OpNode(char o, Node* l, Node* r) : op(o), left(l), right(r) {}
    ~OpNode() {
        delete left;
        delete right;
    }
    int evaluate() const override {
        int leftVal = left->evaluate();
        int rightVal = right->evaluate();
        if (op == '+') {
            return leftVal + rightVal;
        } else if (op == '-') {
            return leftVal - rightVal;
        } else if (op == '*') {
            return leftVal * rightVal;
        } else {  // '/'
            return leftVal / rightVal;
        }
    }
};

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input 
 * and returns the expression tree representing it as a Node.
 */

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {
        stack<Node*> st;
        for (string& token : postfix) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                Node* right = st.top();
                st.pop();
                Node* left = st.top();
                st.pop();
                st.push(new OpNode(token[0], left, right));
            } else {
                st.push(new NumNode(stoi(token)));
            }
        }
        return st.top();
    }
};


/**
 * Your TreeBuilder object will be instantiated and called as such:
 * TreeBuilder* obj = new TreeBuilder();
 * Node* expTree = obj->buildTree(postfix);
 * int ans = expTree->evaluate();
 */