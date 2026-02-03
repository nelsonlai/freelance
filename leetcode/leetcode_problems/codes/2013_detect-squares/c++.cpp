/*
 * Problem: Detect Squares
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Store points in hash map, for query check all possible squares
 * Time Complexity: O(n) for count where n is number of points
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class DetectSquares {
private:
    unordered_map<string, int> points;
    
    string getKey(int x, int y) {
        return to_string(x) + "," + to_string(y);
    }

public:
    DetectSquares() {
        
    }
    
    void add(vector<int> point) {
        string key = getKey(point[0], point[1]);
        points[key]++;
    }
    
    int count(vector<int> point) {
        int x = point[0], y = point[1];
        int result = 0;
        
        for (auto& [key, count] : points) {
            size_t pos = key.find(',');
            int px = stoi(key.substr(0, pos));
            int py = stoi(key.substr(pos + 1));
            
            if (px == x && py == y) {
                continue;
            }
            
            // Check if can form square: (x, y), (px, py), (x, py), (px, y)
            if (abs(px - x) == abs(py - y) && abs(px - x) > 0) {
                string corner1 = getKey(x, py);
                string corner2 = getKey(px, y);
                
                if (points.find(corner1) != points.end() && 
                    points.find(corner2) != points.end()) {
                    result += count * points[corner1] * points[corner2];
                }
            }
        }
        
        return result;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */