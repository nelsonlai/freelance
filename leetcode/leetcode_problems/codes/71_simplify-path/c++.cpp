/*
 * Problem: Simplify Path
 * Difficulty: Medium
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        stringstream ss(path);
        string part;
        vector<string> stack;
        
        while (getline(ss, part, '/')) {
            if (part.empty() || part == ".") {
                continue;
            } else if (part == "..") {
                if (!stack.empty()) {
                    stack.pop_back();
                }
            } else {
                stack.push_back(part);
            }
        }
        
        if (stack.empty()) {
            return "/";
        }
        
        string result;
        for (const string& s : stack) {
            result += "/" + s;
        }
        
        return result;
    }
};