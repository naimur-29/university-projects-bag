#include <iostream>
#include <string>

// Classes:
class Bank {
protected:
    std::string username;
    int account_id;
    int balance;

public:
    Bank(std::string name, int bal);
    bool transfer_balance(Bank &target_bank, int amount);
    bool deposit(int amount);
    bool withdraw(int amount);
    void display();
};

// Functions:
Bank::Bank(std::string name, int bal) {
    username = name;
    account_id = bal*2 + 12324;
    balance = bal;
}

bool Bank::transfer_balance(Bank &target_bank, int amount) {
    bool isWithdrawn;

    isWithdrawn = withdraw(amount);
    if (isWithdrawn)
        target_bank.deposit(amount);

    return isWithdrawn;
}

bool Bank::deposit(int amount) {

    balance += amount;

    return amount > 0;
}

bool Bank::withdraw(int amount) {
    bool isWithdrawn = (amount > 0 && amount <= balance);

    if (isWithdrawn)
        balance -= amount;

    return isWithdrawn;
}

void Bank::display() {
    std::cout << "\nAccount ID: " << account_id << std::endl;
    std::cout << "User Name: " << username << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}

int main() {
    // Create Accounts:
    std::string name;
    int bal;
    
    // Bank A:
    std::cout << "Create BankA account:" << std::endl;
    std::cout << "User Name: ";
    std::cin >> name;
    std::cout << "Balance: ";
    std::cin >> bal;
    Bank bank_a(name, bal);

    // Bank B:
    std::cout << "\nCreate BankB account:" << std::endl;
    std::cout << "User Name: ";
    std::cin >> name;
    std::cout << "Balance: ";
    std::cin >> bal;
    Bank bank_b(name, bal);

    // Show Info:
    bank_a.display();
    bank_b.display();

    // Transfer:
    int amount;
    bool isTransferSuccess;

    std::cout << "\nEnter the amount you want to transfer: ";
    std::cin >> amount;
    isTransferSuccess = bank_b.transfer_balance(bank_a, amount);

    if (isTransferSuccess)
        std::cout << "Transfer Success!" << std::endl;
    else
        std::cout << "Transfer Failed!" << std::endl;

    // Show Info:
    bank_a.display();
    bank_b.display();

    return 0;
}