/*
 * Problem: Design Browser History
 * Difficulty: Medium
 * Tags: array, string, linked_list, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class BrowserHistory {
private:
    vector<string> history;
    int current;
    int end;

public:
    BrowserHistory(string homepage) {
        history.push_back(homepage);
        current = 0;
        end = 0;
    }
    
    void visit(string url) {
        current++;
        if (current < history.size()) {
            history[current] = url;
        } else {
            history.push_back(url);
        }
        end = current;
    }
    
    string back(int steps) {
        current = max(0, current - steps);
        return history[current];
    }
    
    string forward(int steps) {
        current = min(end, current + steps);
        return history[current];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */