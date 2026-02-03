/*
 * Problem: Smallest Greater Multiple Made of Two Digits
 * Difficulty: Medium
 * Tags: math, BFS
 * 
 * Approach: BFS to find smallest number > k made of only digit1 and digit2
 * Time Complexity: O(2^log(k)) in worst case
 * Space Complexity: O(2^log(k))
 */

#include <queue>
#include <unordered_set>
#include <set>

using namespace std;

class Solution {
public:
    int findInteger(int k, int digit1, int digit2) {
        set<int> digits;
        if (digit1 != digit2) {
            digits.insert(digit1);
            digits.insert(digit2);
        } else {
            digits.insert(digit1);
        }
        
        queue<long long> q;
        q.push(0);
        unordered_set<long long> visited;
        visited.insert(0);
        
        while (!q.empty()) {
            long long num = q.front();
            q.pop();
            
            for (int digit : digits) {
                long long nextNum = num * 10 + digit;
                if (nextNum > k) {
                    return nextNum;
                }
                
                if (nextNum > 0 && visited.find(nextNum) == visited.end()) {
                    visited.insert(nextNum);
                    q.push(nextNum);
                }
            }
        }
        
        return -1;
    }
};