
## In python class, how many double underscore methods are available? What their purpose on each? - Homework #1

class BankAccount:      ## Object class
    def __init__(self, owner, balance):
        self.owner = owner
        self.__balance = balance  # private attribute

    def deposit(self, amount):
        self.__balance += amount

    def withdraw(self, amount):
        if amount <= self.__balance:
            self.__balance -= amount
        else:
            print("Insufficient funds.")

    def get_balance(self):
        return self.__balance

if __name__ == "__main__":
    account = BankAccount("John Doe", 1000)
    # account.__balance = 2000  # Attempt to modify private attribute directly
    # print(account.__balance)   # This will not print the actual balance
    account.deposit(500)
    account.withdraw(200)
    print(account.get_balance())