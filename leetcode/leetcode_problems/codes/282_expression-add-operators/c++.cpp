/*
 * Problem: Expression Add Operators
 * Difficulty: Hard
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void backtrack(string& num, int target, int index, string path, 
                  long value, long prev, vector<string>& result) {
        if (index == num.length()) {
            if (value == target) {
                result.push_back(path);
            }
            return;
        }
        
        for (int i = index; i < num.length(); i++) {
            if (i > index && num[index] == '0') {
                break;
            }
            
            long curr = stol(num.substr(index, i - index + 1));
            
            if (index == 0) {
                backtrack(num, target, i + 1, to_string(curr), curr, curr, result);
            } else {
                backtrack(num, target, i + 1, path + "+" + to_string(curr), value + curr, curr, result);
                backtrack(num, target, i + 1, path + "-" + to_string(curr), value - curr, -curr, result);
                backtrack(num, target, i + 1, path + "*" + to_string(curr), value - prev + prev * curr, prev * curr, result);
            }
        }
    }

public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        backtrack(num, target, 0, "", 0, 0, result);
        return result;
    }
};