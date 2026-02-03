/*
 * Problem: Longest Absolute File Path
 * Difficulty: Medium
 * Tags: string, tree, search, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        stringstream ss(input);
        string line;
        vector<int> stack;
        int maxLength = 0;
        
        while (getline(ss, line)) {
            int depth = 0;
            while (depth < line.length() && line[depth] == '\t') {
                depth++;
            }
            string name = line.substr(depth);
            
            while (stack.size() > depth) {
                stack.pop_back();
            }
            
            int currentLength = (stack.empty() ? 0 : stack.back()) + name.length() + (stack.empty() ? 0 : 1);
            
            if (name.find('.') != string::npos) {
                maxLength = max(maxLength, currentLength);
            } else {
                stack.push_back(currentLength);
            }
        }
        
        return maxLength;
    }
};