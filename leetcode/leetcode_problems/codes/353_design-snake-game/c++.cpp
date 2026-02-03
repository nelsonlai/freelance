/*
 * Problem: Design Snake Game
 * Difficulty: Medium
 * Tags: array, string, hash, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

class SnakeGame {
private:
    int width;
    int height;
    deque<vector<int>> food;
    deque<vector<int>> snake;
    unordered_map<string, vector<int>> directions;
    int score;

public:
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        this->width = width;
        this->height = height;
        this->food = deque<vector<int>>(food.begin(), food.end());
        this->snake.push_back({0, 0});
        this->directions["U"] = {-1, 0};
        this->directions["D"] = {1, 0};
        this->directions["L"] = {0, -1};
        this->directions["R"] = {0, 1};
        this->score = 0;
    }
    
    int move(string direction) {
        vector<int> dir = directions[direction];
        vector<int> head = snake.front();
        vector<int> newHead = {head[0] + dir[0], head[1] + dir[1]};
        
        if (newHead[0] < 0 || newHead[0] >= height || 
            newHead[1] < 0 || newHead[1] >= width) {
            return -1;
        }
        
        if (!food.empty() && newHead == food.front()) {
            food.pop_front();
            score++;
        } else {
            snake.pop_back();
        }
        
        for (auto& body : snake) {
            if (body == newHead) {
                return -1;
            }
        }
        
        snake.push_front(newHead);
        return score;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */