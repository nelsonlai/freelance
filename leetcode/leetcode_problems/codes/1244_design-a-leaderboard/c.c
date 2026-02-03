/*
 * Problem: Design A Leaderboard
 * Difficulty: Medium
 * Tags: hash, sort
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} Leaderboard;


Leaderboard* leaderboardCreate() {
    
}

void leaderboardAddScore(Leaderboard* obj, int playerId, int score) {
    
}

int leaderboardTop(Leaderboard* obj, int K) {
    
}

void leaderboardReset(Leaderboard* obj, int playerId) {
    
}

void leaderboardFree(Leaderboard* obj) {
    
}

/**
 * Your Leaderboard struct will be instantiated and called as such:
 * Leaderboard* obj = leaderboardCreate();
 * leaderboardAddScore(obj, playerId, score);
 
 * int param_2 = leaderboardTop(obj, K);
 
 * leaderboardReset(obj, playerId);
 
 * leaderboardFree(obj);
*/