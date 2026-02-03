/*
 * Problem: Design Authentication Manager
 * Difficulty: Medium
 * Tags: string, hash, linked_list
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} AuthenticationManager;


AuthenticationManager* authenticationManagerCreate(int timeToLive) {
    
}

void authenticationManagerGenerate(AuthenticationManager* obj, char* tokenId, int currentTime) {
    
}

void authenticationManagerRenew(AuthenticationManager* obj, char* tokenId, int currentTime) {
    
}

int authenticationManagerCountUnexpiredTokens(AuthenticationManager* obj, int currentTime) {
    
}

void authenticationManagerFree(AuthenticationManager* obj) {
    
}

/**
 * Your AuthenticationManager struct will be instantiated and called as such:
 * AuthenticationManager* obj = authenticationManagerCreate(timeToLive);
 * authenticationManagerGenerate(obj, tokenId, currentTime);
 
 * authenticationManagerRenew(obj, tokenId, currentTime);
 
 * int param_3 = authenticationManagerCountUnexpiredTokens(obj, currentTime);
 
 * authenticationManagerFree(obj);
*/