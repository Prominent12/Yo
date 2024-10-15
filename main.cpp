
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
public:
    string accountNumber;
    string username;
    string password;
    double balance;

    Account(string accNum, string user, string pass)
        : accountNumber(accNum), username(user), password(pass), balance(0.0) {}

    bool validatePassword(const string &pass) {
        return password == pass;
    }
};

class BankingSystem {
private:
    vector<Account> accounts;

public:
    void createAccount() {
        string accountNumber, username, password;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        accounts.emplace_back(accountNumber, username, password);
        cout << "Account created successfully!\n";
    }

    Account* login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (auto &account : accounts) {
            if (account.username == username && account.validatePassword(password)) {
                cout << "Login successful!\n";
                return &account;
            }
        }
        cout << "Invalid username or password.\n";
        return nullptr;
    }

    void deposit(Account &account) {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            account.balance += amount;
            cout << "Deposit successful! New balance: R" << account.balance << "\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(Account &account) {
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (amount > 0 && amount <= account.balance) {
            account.balance -= amount;
            cout << "Withdrawal successful! New balance: R" << account.balance << "\n";
        } else {
            cout << "Insufficient funds or invalid withdrawal amount.\n";
        }
    }

    void checkBalance(const Account &account) {
        cout << "Your current balance is: R" << account.balance << "\n";
    }

    void menu(Account &account) {
        int choice;
        do {
            cout << "\n1. Deposit Money\n2. Withdraw Money\n3. Check Balance\n4. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    deposit(account);
                    break;
                case 2:
                    withdraw(account);
                    break;
                case 3:
                    checkBalance(account);
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    BankingSystem bankingSystem;
    int option;

    do {
        cout << "\n1. Create Account\n2. Login\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                bankingSystem.createAccount();
                break;
            case 2: {
                Account *account = bankingSystem.login();
                if (account) {
                    bankingSystem.menu(*account);
                }
                break;
            }
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 3);

    return 0;
}

