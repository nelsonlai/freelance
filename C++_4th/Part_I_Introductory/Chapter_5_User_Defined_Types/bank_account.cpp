#include <iostream>
#include <string>
#include <stdexcept>

// BankAccount class demonstrating basic class design principles
class BankAccount {
private:
    double balance;
    std::string account_number;
    std::string account_holder;
    
public:
    // Constructor
    BankAccount(const std::string& account_number, 
                const std::string& account_holder, 
                double initial_balance = 0.0)
        : account_number(account_number), 
          account_holder(account_holder), 
          balance(initial_balance) {
        std::cout << "Account created: " << account_number 
                  << " for " << account_holder 
                  << " with initial balance: $" << balance << std::endl;
    }
    
    // Destructor
    ~BankAccount() {
        std::cout << "Account " << account_number << " closed." << std::endl;
    }
    
    // Copy constructor
    BankAccount(const BankAccount& other)
        : account_number(other.account_number + "_copy"),
          account_holder(other.account_holder),
          balance(other.balance) {
        std::cout << "Account copied: " << account_number << std::endl;
    }
    
    // Copy assignment operator
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            account_holder = other.account_holder;
            balance = other.balance;
            // Note: account_number is not copied to maintain uniqueness
            std::cout << "Account assigned: " << account_number << std::endl;
        }
        return *this;
    }
    
    // Member functions
    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive");
        }
        balance += amount;
        std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        if (amount > balance) {
            std::cout << "Insufficient funds. Requested: $" << amount 
                      << ", Available: $" << balance << std::endl;
            return false;
        }
        balance -= amount;
        std::cout << "Withdrew $" << amount << ". New balance: $" << balance << std::endl;
        return true;
    }
    
    double get_balance() const {
        return balance;
    }
    
    const std::string& get_account_number() const {
        return account_number;
    }
    
    const std::string& get_account_holder() const {
        return account_holder;
    }
    
    void display_info() const {
        std::cout << "Account Information:" << std::endl;
        std::cout << "  Account Number: " << account_number << std::endl;
        std::cout << "  Account Holder: " << account_holder << std::endl;
        std::cout << "  Balance: $" << balance << std::endl;
    }
    
    // Static member function
    static void display_bank_info() {
        std::cout << "Welcome to SecureBank - Your Trusted Financial Partner" << std::endl;
    }
    
    // Friend function declaration (for operator overloading)
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
};

// Friend function implementation
std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
    os << "Account[" << account.account_number << "]: $" << account.balance;
    return os;
}

// Demonstrates the BankAccount class
int main() {
    std::cout << "Bank Account Class Demonstration" << std::endl;
    std::cout << "================================" << std::endl;
    
    // 1. Static member function
    std::cout << "\n1. STATIC MEMBER FUNCTION:" << std::endl;
    BankAccount::display_bank_info();
    
    // 2. Creating accounts
    std::cout << "\n2. CREATING ACCOUNTS:" << std::endl;
    
    BankAccount account1("ACC001", "Alice Johnson", 1000.0);
    BankAccount account2("ACC002", "Bob Smith", 500.0);
    
    // 3. Displaying account information
    std::cout << "\n3. ACCOUNT INFORMATION:" << std::endl;
    account1.display_info();
    std::cout << std::endl;
    account2.display_info();
    
    // 4. Depositing money
    std::cout << "\n4. DEPOSITING MONEY:" << std::endl;
    account1.deposit(250.0);
    account2.deposit(100.0);
    
    // 5. Withdrawing money
    std::cout << "\n5. WITHDRAWING MONEY:" << std::endl;
    account1.withdraw(200.0);
    account2.withdraw(700.0);  // This should fail due to insufficient funds
    
    // 6. Using operator overloading
    std::cout << "\n6. OPERATOR OVERLOADING:" << std::endl;
    std::cout << "Account 1: " << account1 << std::endl;
    std::cout << "Account 2: " << account2 << std::endl;
    
    // 7. Copy constructor
    std::cout << "\n7. COPY CONSTRUCTOR:" << std::endl;
    BankAccount account3 = account1;  // Copy constructor called
    
    // 8. Copy assignment
    std::cout << "\n8. COPY ASSIGNMENT:" << std::endl;
    account3 = account2;  // Copy assignment called
    
    // 9. Error handling
    std::cout << "\n9. ERROR HANDLING:" << std::endl;
    try {
        account1.deposit(-100.0);  // This will throw an exception
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // 10. Final balances
    std::cout << "\n10. FINAL BALANCES:" << std::endl;
    std::cout << "Account 1 balance: $" << account1.get_balance() << std::endl;
    std::cout << "Account 2 balance: $" << account2.get_balance() << std::endl;
    std::cout << "Account 3 balance: $" << account3.get_balance() << std::endl;
    
    // Destructors will be called automatically when objects go out of scope
    std::cout << "\nAccounts will be destroyed when program ends..." << std::endl;
    
    return 0;
}
