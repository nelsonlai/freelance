/*
 * Problem: Simple Bank System
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} Bank;


Bank* bankCreate(long long* balance, int balanceSize) {
    
}

bool bankTransfer(Bank* obj, int account1, int account2, long long money) {
    
}

bool bankDeposit(Bank* obj, int account, long long money) {
    
}

bool bankWithdraw(Bank* obj, int account, long long money) {
    
}

void bankFree(Bank* obj) {
    
}

/**
 * Your Bank struct will be instantiated and called as such:
 * Bank* obj = bankCreate(balance, balanceSize);
 * bool param_1 = bankTransfer(obj, account1, account2, money);
 
 * bool param_2 = bankDeposit(obj, account, money);
 
 * bool param_3 = bankWithdraw(obj, account, money);
 
 * bankFree(obj);
*/