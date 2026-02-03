#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Directions: right, left, down, up, down-right, down-left, up-right, up-left
int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
const int DIRS = 8;

bool searchFrom(const vector<vector<char>>& board, int x, int y, const string& word, int dir) {
    int n = board.size();
    int m = board[0].size();

    for (int i = 0; i < word.size(); ++i) {
        int nx = x + dx[dir] * i;
        int ny = y + dy[dir] * i;

        if (nx < 0 || ny < 0 || nx >= n || ny >= m)
            return false;
        if (board[nx][ny] != word[i])
            return false;
    }
    return true;
}

bool findWord(const vector<vector<char>>& board, const string& word, int& out_x, int& out_y, int& out_dir) {
    int n = board.size();
    int m = board[0].size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int d = 0; d < DIRS; ++d) {
                if (searchFrom(board, i, j, word, d)) {
                    out_x = i;
                    out_y = j;
                    out_dir = d;
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    vector<vector<char>> board = {
        {'t','h','i','s'},
        {'w','a','t','s'},
        {'o','a','h','g'},
        {'f','g','d','t'}
    };

    vector<string> words = {"this", "two", "fat", "that"};

    for (const string& word : words) {
        int x, y, dir;
        if (findWord(board, word, x, y, dir)) {
            cout << "Word \"" << word << "\" found at (" << x << ", " << y << ") in direction " << dir << endl;
        } else {
            cout << "Word \"" << word << "\" not found." << endl;
        }
    }

    return 0;
}

// -- optimization with a Trie