/*
 * Problem: The k-th Lexicographical String of All Happy Strings of Length n
 * Difficulty: Medium
 * Tags: string, graph, sort
 * 
 * Approach: Generate happy strings in lexicographical order, return k-th
 * Time Complexity: O(n * 3^n) in worst case
 * Space Complexity: O(n) for recursion
 */

#include <string>

using namespace std;

class Solution {
private:
    string result = "";
    int count = 0;
    
    void backtrack(string& current, int n, int k) {
        if (current.length() == n) {
            count++;
            if (count == k) {
                result = current;
            }
            return;
        }
        
        for (char c : {'a', 'b', 'c'}) {
            if (current.empty() || current.back() != c) {
                current += c;
                backtrack(current, n, k);
                current.pop_back();
                if (!result.empty()) {
                    return;
                }
            }
        }
    }

public:
    string getHappyString(int n, int k) {
        string current = "";
        backtrack(current, n, k);
        return result;
    }
};