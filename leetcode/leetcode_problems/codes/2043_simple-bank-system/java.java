/**
 * Problem: Simple Bank System
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Simple bank operations with account validation
 * Time Complexity: O(1) for each operation
 * Space Complexity: O(n) for accounts
 */

class Bank {
    private long[] balance;
    private int n;

    public Bank(long[] balance) {
        this.balance = balance;
        this.n = balance.length;
    }
    
    public boolean transfer(int account1, int account2, long money) {
        if (account1 < 1 || account1 > n || account2 < 1 || account2 > n) {
            return false;
        }
        if (balance[account1 - 1] < money) {
            return false;
        }
        balance[account1 - 1] -= money;
        balance[account2 - 1] += money;
        return true;
    }
    
    public boolean deposit(int account, long money) {
        if (account < 1 || account > n) {
            return false;
        }
        balance[account - 1] += money;
        return true;
    }
    
    public boolean withdraw(int account, long money) {
        if (account < 1 || account > n) {
            return false;
        }
        if (balance[account - 1] < money) {
            return false;
        }
        balance[account - 1] -= money;
        return true;
    }
}

/**
 * Your Bank object will be instantiated and called as such:
 * Bank obj = new Bank(balance);
 * boolean param_1 = obj.transfer(account1,account2,money);
 * boolean param_2 = obj.deposit(account,money);
 * boolean param_3 = obj.withdraw(account,money);
 */