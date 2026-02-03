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
#include <string>
#include <limits>   // for std::numeric_limits

class BankAccount {
protected:
    std::string name;
    double balance;
    std::string password;
    bool is_logged_in = false;

public:
    BankAccount() : balance(0.0) {
        std::cout << "BankAccount created.\n";
    }


    void registerAccount() {
        std::cout << "Set your name: ";
        std::getline(std::cin, name);
        std::cout << "Set your password: ";
        std::getline(std::cin, password);
        std::cout << "Account created successfully.\n";
    }

    void login() {
        std::string input;
        std::cout << "Login:\n";
        std::cout << "Enter name: ";
        std::getline(std::cin, input);
        if (input != name) {
            std::cout << "Wrong name!\n";
            return;
        }
        std::cout << "Enter password: ";
        std::getline(std::cin, input);
        if (input != password) {
            std::cout << "Wrong password!\n";
            return;
        }
        std::cout << "Logged in!\n";
        is_logged_in = true;
    }

    void deposit(double amt) {
        if (!is_logged_in) {
            std::cout << "Login first!\n";
            return;
        }
        if (amt > 0) {
            balance += amt;
            std::cout << "Deposited $" << amt << "\n";
        } else {
            std::cout << "Amount must be positive.\n";
        }
    }

    void withdraw(double amt) {
        if (!is_logged_in) {
            std::cout << "Login first!\n";
            return;
        }
        if (amt <= 0) {
            std::cout << "Amount must be positive.\n";
        } else if (amt <= balance) {
            balance -= amt;
            std::cout << "Withdrew $" << amt << "\n";
        } else {
            std::cout << "Invalid withdraw amount!\n";
        }
    }

    double getBalance() const { return balance; }
};

class Auditor : protected BankAccount {
public:
    // Inspect a specific account (friend access lets us read name/balance if we want)
    void view_account(const BankAccount& acc) const {
        std::cout << "[AUDITOR REPORT] Account Holder: " << acc.name
                  << " | Balance: $" << acc.balance << "\n";
    }
};

// helper: flush leftover input to end of line
static void flush_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    BankAccount acc;
    Auditor auditor;

    acc.registerAccount();
    acc.login();

    char option;
    do {
        std::cout << "\nChoose: (l)ogin, (d)eposit, (w)ithdraw, (a)udit, (q)uit: ";
        if (!(std::cin >> option)) return 0;
        flush_line();  // clear newline after reading the option

        switch (option) {
            case 'l': {
                acc.login();
                break;
            }
            case 'd': {
                std::cout << "Enter amount to deposit: ";
                double amount{};
                if (!(std::cin >> amount)) {
                    std::cout << "Invalid number.\n";
                    std::cin.clear();
                    flush_line();
                    break;
                }
                flush_line();
                acc.deposit(amount);
                break;
            }
            case 'w': {
                std::cout << "Enter amount to withdraw: ";
                double amount{};
                if (!(std::cin >> amount)) {
                    std::cout << "Invalid number.\n";
                    std::cin.clear();
                    flush_line();
                    break;
                }
                flush_line();
                acc.withdraw(amount);
                break;   // <-- FIXED: prevent fall-through
            }
            case 'a': {
                auditor.view_account(&acc);  // audit the *existing* account
                std::cout << "Account Balance: $" << acc.getBalance() << "\n";
                break;
            }
            case 'q':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
                break;
        }
    } while (option != 'q');

    return 0;
}