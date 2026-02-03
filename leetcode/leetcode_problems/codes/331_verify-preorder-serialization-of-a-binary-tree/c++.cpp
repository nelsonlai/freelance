/*
 * Problem: Verify Preorder Serialization of a Binary Tree
 * Difficulty: Medium
 * Tags: string, tree, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    bool isValidSerialization(string preorder) {
        stringstream ss(preorder);
        string node;
        int slots = 1;
        
        while (getline(ss, node, ',')) {
            slots--;
            if (slots < 0) {
                return false;
            }
            if (node != "#") {
                slots += 2;
            }
        }
        
        return slots == 0;
    }
};