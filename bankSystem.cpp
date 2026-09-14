#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    double balance;

public:

    // Function to create a new account
    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "\nAccount created successfully!\n";
    }

    // Display account information
    void displayAccount()
    {
        cout << "\n-----------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs. " << balance;
        cout << "\n-----------------------------";
    }

    // Return account number
    int getAccountNumber()
    {
        return accountNumber;
    }

    // Deposit money
    void deposit()
    {
        double amount;

        cout << "\nEnter amount to deposit: Rs. ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
            return;
        }

        balance += amount;

        cout << "Amount deposited successfully!\n";
        cout << "New Balance: Rs. " << balance << endl;
    }

    // Withdraw money
    void withdraw()
    {
        double amount;

        cout << "\nEnter amount to withdraw: Rs. ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
        }
        else if (amount > balance)
        {
            cout << "Insufficient balance!\n";
        }
        else
        {
            balance -= amount;

            cout << "Amount withdrawn successfully!\n";
            cout << "Remaining Balance: Rs. "
                 << balance << endl;
        }
    }

    // Check balance
    void checkBalance()
    {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nCustomer Name : " << name;
        cout << "\nCurrent Balance: Rs. "
             << balance << endl;
    }
};


// Check if an account already exists
bool accountExists(int accountNumber)
{
    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accountNumber)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


// Create a new account
void addAccount()
{
    BankAccount account;

    account.createAccount();

    if (accountExists(account.getAccountNumber()))
    {
        cout << "\nAccount number already exists!\n";
        return;
    }

    ofstream file("bank.dat", ios::binary | ios::app);

    file.write((char*)&account, sizeof(account));

    file.close();

    cout << "\nAccount saved successfully!\n";
}


// Deposit money into an account
void depositMoney()
{
    int accountNumber;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    fstream file("bank.dat",
                 ios::binary | ios::in | ios::out);

    BankAccount account;

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accountNumber)
        {
            account.deposit();

            // Move file pointer to beginning of current record
            file.seekp(-static_cast<int>(sizeof(account)),
                       ios::cur);

            file.write((char*)&account, sizeof(account));

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount not found!\n";
}


// Withdraw money from an account
void withdrawMoney()
{
    int accountNumber;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    fstream file("bank.dat",
                 ios::binary | ios::in | ios::out);

    BankAccount account;

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accountNumber)
        {
            account.withdraw();

            // Move file pointer to beginning of current record
            file.seekp(-static_cast<int>(sizeof(account)),
                       ios::cur);

            file.write((char*)&account, sizeof(account));

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount not found!\n";
}


// Check account balance
void balanceInquiry()
{
    int accountNumber;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    ifstream file("bank.dat", ios::binary);

    BankAccount account;

    while (file.read((char*)&account, sizeof(account)))
    {
        if (account.getAccountNumber() == accountNumber)
        {
            account.checkBalance();

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount not found!\n";
}


// Display all accounts
void displayAllAccounts()
{
    ifstream file("bank.dat", ios::binary);

    BankAccount account;

    bool found = false;

    cout << "\n========== ALL BANK ACCOUNTS ==========\n";

    while (file.read((char*)&account, sizeof(account)))
    {
        account.displayAccount();
        found = true;
    }

    file.close();

    if (!found)
        cout << "\nNo accounts found!\n";
}


// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\n========================================";
        cout << "\n       BANK MANAGEMENT SYSTEM";
        cout << "\n========================================";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";
        cout << "\n========================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            balanceInquiry();
            break;

        case 5:
            displayAllAccounts();
            break;

        case 6:
            cout << "\nThank you for using Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}