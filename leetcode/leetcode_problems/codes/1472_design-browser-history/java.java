/**
 * Problem: Design Browser History
 * Difficulty: Medium
 * Tags: array, string, linked_list, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class BrowserHistory {
    private List<String> history;
    private int current;
    private int end;

    public BrowserHistory(String homepage) {
        history = new ArrayList<>();
        history.add(homepage);
        current = 0;
        end = 0;
    }
    
    public void visit(String url) {
        current++;
        if (current < history.size()) {
            history.set(current, url);
        } else {
            history.add(url);
        }
        end = current;
    }
    
    public String back(int steps) {
        current = Math.max(0, current - steps);
        return history.get(current);
    }
    
    public String forward(int steps) {
        current = Math.min(end, current + steps);
        return history.get(current);
    }
}

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory obj = new BrowserHistory(homepage);
 * obj.visit(url);
 * String param_2 = obj.back(steps);
 * String param_3 = obj.forward(steps);
 */