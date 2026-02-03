/*
 * Problem: Number of Pairs of Interchangeable Rectangles
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Count rectangles with same aspect ratio, calculate pairs using n*(n-1)/2
 * Time Complexity: O(n) where n is number of rectangles
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class Solution {
private:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        unordered_map<string, int> ratioCount;
        
        for (auto& rect : rectangles) {
            int w = rect[0], h = rect[1];
            int g = gcd(w, h);
            string ratio = to_string(w / g) + "/" + to_string(h / g);
            ratioCount[ratio]++;
        }
        
        long long result = 0;
        for (auto& [ratio, count] : ratioCount) {
            if (count > 1) {
                result += (long long) count * (count - 1) / 2;
            }
        }
        
        return result;
    }
};