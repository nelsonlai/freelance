/*
 * Problem: Design a File Sharing System
 * Difficulty: Medium
 * Tags: hash, sort, queue, heap
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

class FileSharing {
private:
    unordered_map<int, unordered_set<int>> userChunks;
    unordered_map<int, set<int>> chunkUsers;
    priority_queue<int, vector<int>, greater<int>> availableIds;
    int nextId;

public:
    FileSharing(int m) {
        for (int i = 1; i <= m; i++) {
            chunkUsers[i] = set<int>();
        }
        nextId = 1;
    }
    
    int join(vector<int> ownedChunks) {
        int userId;
        if (!availableIds.empty()) {
            userId = availableIds.top();
            availableIds.pop();
        } else {
            userId = nextId++;
        }
        
        userChunks[userId] = unordered_set<int>(ownedChunks.begin(), ownedChunks.end());
        for (int chunk : ownedChunks) {
            chunkUsers[chunk].insert(userId);
        }
        
        return userId;
    }
    
    void leave(int userID) {
        for (int chunk : userChunks[userID]) {
            chunkUsers[chunk].erase(userID);
        }
        userChunks.erase(userID);
        availableIds.push(userID);
    }
    
    vector<int> request(int userID, int chunkID) {
        vector<int> users(chunkUsers[chunkID].begin(), chunkUsers[chunkID].end());
        if (!users.empty()) {
            userChunks[userID].insert(chunkID);
            chunkUsers[chunkID].insert(userID);
        }
        return users;
    }
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */