/*
 * C++ PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates C++ programming concepts and techniques:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental C++ PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 8 directions (row, col) deltas: right, left, down, up, and 4 diagonals
int dirX[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
int dirY[] = { 1, -1, 0, 0, 1, -1, -1, 1 };

// Grid dimensions
int rows, cols;

// Function to check if a word is present starting from (x, y) in a certain direction
bool searchWord(const vector<vector<char>>& board, const string& word,
                int x, int y, int dx, int dy, pair<int,int>& endPos) {
    int n = word.size();
    int i;
    for (i = 0; i < n; ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || board[nx][ny] != word[i]) {
            return false;
        }
    }
    endPos = { x + (n - 1) * dx, y + (n - 1) * dy };
    return true;
}

void findWords(const vector<vector<char>>& board, const vector<string>& words) {
    rows = board.size();
    cols = board[0].size();

    for (const string& word : words) {
        bool found = false;
        for (int x = 0; x < rows && !found; ++x) {
            for (int y = 0; y < cols && !found; ++y) {
                if (board[x][y] == word[0]) {
                    for (int d = 0; d < 8; ++d) {
                        pair<int, int> endPos;
                        if (searchWord(board, word, x, y, dirX[d], dirY[d], endPos)) {
                            cout << "Found \"" << word << "\" from (" << x+1 << "," << y+1 << ") to ("
                                 << endPos.first+1 << "," << endPos.second+1 << ")\n";
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        if (!found)
            cout << "\"" << word << "\" not found in the puzzle.\n";
    }
}

int main() {
    vector<vector<char>> board = {
        {'t','h','i','s'},
        {'w','a','t','s'},
        {'o','a','h','g'},
        {'f','g','d','t'}
    };

    vector<string> words = { "this", "two", "fat", "that" };

    findWords(board, words);

    return 0;
}