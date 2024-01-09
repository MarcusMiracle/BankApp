// Programmer: Miracle Marcus
// Program: Bank App Implementation

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

struct BirthDate {
    int day = 0;
    int month = 0;
    int year = 0;
};
struct Account {
    int accountNumber = 0;
    string firstName;
    string lastName;
    string address;
    string phoneNo;
    double balance = 0;
    BirthDate dateOfBirth;
};

// Function prototypes
void openAccount(fstream& outFile, Account accounts[], int numAccounts, int& lastAccountNumber);
void closeAccount(fstream& outFile, Account accounts[], int numAccounts);
void deposit(fstream& outFile, Account accounts[], int numAccounts);
void withdraw(fstream& outFile, Account accounts[], int numAccounts);
void accountInfo(Account accounts[], int numAccounts);
void printAllAccounts(Account accounts[], int numAccounts);
void printAccountInfo(Account& account);
void searchForAccount(Account accounts[], int numAccounts);
bool isValidDate(const BirthDate& date);


const int MAX_ACCOUNTS = 100;

int main() {

    // Open a file for writing
    fstream outFile;
    outFile.open ("Miracle's Bank.txt", ios::app);

    // Initialize the array of accounts
    Account newAccounts[MAX_ACCOUNTS];

    int numAccounts = 1;
    int lastAccountNumber = 230;

    while (true) {

        // Display the menu
        cout << "\nO: Open account!" << endl;
        cout << "C: Close account!" << endl;
        cout << "D: Deposit!" << endl;
        cout << "W: Withdraw!" << endl;
        cout << "A: Account info!" << endl;
        cout << "P: Print all accounts!" << endl;
        cout << "S: Search for account!" << endl;
        cout << "Q: Quit!" << endl;
        cout << "Enter operation: ";

        char operation;
        cin >> operation;

        operation = toupper(operation);


        if (operation == 'O') {
            // Open account
            openAccount(outFile, newAccounts, numAccounts, lastAccountNumber);
        }
        else if (operation == 'C') {
            // Close account
            closeAccount(outFile, newAccounts, numAccounts);
        }
        else if (operation == 'D') {
            // Deposit
            deposit(outFile, newAccounts, numAccounts);
        }
        else if (operation == 'W') {
            // Withdraw
            withdraw(outFile, newAccounts, numAccounts);
        }
        else if (operation == 'A') {
            // Account info
            accountInfo(newAccounts, numAccounts);
        }
        else if (operation == 'P') {
            // Print all accounts
            printAllAccounts(newAccounts, numAccounts);
        }
        else if (operation == 'S') {
            // Search for account
            searchForAccount(newAccounts, numAccounts);
        }
        else if (operation == 'Q') {
            // Exit
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid operation!" << endl;
        }
    }

    // Close the file
    outFile.close();

    return 0;
}



// Function implementations
void openAccount(fstream& outFile, Account accounts[], int numAccounts, int& lastAccountNumber) {

    // Ensure there is space in the array for a new account
    if (numAccounts >= MAX_ACCOUNTS) {
        cout << "Error: Maximum number of accounts reached!" << endl;
        return;
    }


    // Get account information from the user
    string firstName, lastName, address, phoneNo;
    int day, month, year;
    double balance;

    // Assign a unique account number
    int accountNumber = lastAccountNumber++;

    cout << "\nEnter first name: ";
    cin >> firstName;

    cin.ignore();
    cout << "Enter last name: ";
    cin >> lastName;

    cin.ignore();
    cout << "Enter address: ";
    getline(cin, address);

    cout << "Enter phone number: ";
    cin >> phoneNo;

    cout << "Enter initial balance: ";
    cin >> balance;

    // Get date of birth and validate
    bool validDate = false;
    while (!validDate) {
        cout << "Enter date of birth (DD MM YYYY): ";
        cin >> day >> month >> year;

        validDate = isValidDate({ day, month, year });

        if (!validDate) {
            cout << "Invalid date of birth! Please enter a valid date." << endl;
        }
    }

    cout << "Account created successfully!" << endl;
    cout << "Your account number is: " << accountNumber << endl;

    // Create a new account object
    Account newAccount = { accountNumber, firstName, lastName, address, phoneNo, balance, { day, month, year } };

    // Write the account information to the file
    outFile << "Last Account Number: " << lastAccountNumber << endl;
    outFile << "Account Number: " << accountNumber << endl;
    outFile << "First Name: " << firstName << endl;
    outFile << "Last Name: " << lastName << endl;
    outFile << "Address: " << address << endl;
    outFile << "Phone Number: " << phoneNo << endl;
    outFile << "Balance: " << balance << endl;
    outFile << "Birth Day: " << day << endl;
    outFile << "Birth Month: " << month << endl;
    outFile << "Birth Year: " << year << endl;
    outFile << "\n\n";
    outFile << lastAccountNumber;


    // Add the account to the array
    cout << numAccounts - 1;
    accounts[numAccounts - 1] = newAccount;
    numAccounts++;
}

void closeAccount(fstream& outFile, Account accounts[], int numAccounts) {

    // Get the account number to close
    int accountNumber;
    cout << "Enter account number to close: ";
    cin >> accountNumber;

    // Check if the account exists
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            // Rewrite the updated account to the file
            outFile << accounts[i].accountNumber << endl;
            outFile << accounts[i].firstName << endl;
            outFile << accounts[i].lastName << endl;
            outFile << accounts[i].address << endl;
            outFile << accounts[i].phoneNo << endl;
            outFile << accounts[i].balance << endl;
            outFile << accounts[i].dateOfBirth.day << endl;
            outFile << accounts[i].dateOfBirth.month << endl;
            outFile << accounts[i].dateOfBirth.year << endl;

            cout << "Account closed" << endl;

            // Since the account is closed, remove it from the array
            for (int j = i; j < numAccounts - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            numAccounts--;
            return;
        }
    }
}

void deposit(fstream& outFile, Account accounts[], int numAccounts) {
    // Get the account number and deposit amount
    int accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter amount to deposit: ";
    cin >> amount;

    // Find the account
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {

            // Add the deposit amount to the balance
            accounts[i].balance += amount;

            // Write the updated account to the file
            outFile << accounts[i].accountNumber << endl;
            outFile << accounts[i].firstName << endl;
            outFile << accounts[i].lastName << endl;
            outFile << accounts[i].address << endl;
            outFile << accounts[i].phoneNo << endl;
            outFile << accounts[i].balance << endl;
            outFile << accounts[i].dateOfBirth.day << endl;
            outFile << accounts[i].dateOfBirth.month << endl;
            outFile << accounts[i].dateOfBirth.year << endl;

            cout << "Deposit successful!" << endl;
            cout << "Account balance is: €" << accounts[i].balance << endl;
            return;
        }
    }

    cout << "Account not found!" << endl;
}

void withdraw(fstream& outFile, Account accounts[], int numAccounts) {

    // Get the account number and withdrawal amount
    int accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    // Find the account
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            // Check if the withdrawal amount is valid
            if (amount <= accounts[i].balance) {
                // Withdraw the specified amount from the balance
                accounts[i].balance -= amount;

                // Write the updated account to the file
                outFile << accounts[i].accountNumber << endl;
                outFile << accounts[i].firstName << endl;
                outFile << accounts[i].lastName << endl;
                outFile << accounts[i].address << endl;
                outFile << accounts[i].phoneNo << endl;
                outFile << accounts[i].balance << endl;
                outFile << accounts[i].dateOfBirth.day << endl;
                outFile << accounts[i].dateOfBirth.month << endl;
                outFile << accounts[i].dateOfBirth.year << endl;

                cout << "Withdrawal successful!" << endl;
                cout << "Account balance is: €" << accounts[i].balance << endl;
                return;
            }
            else {
                cout << "Insufficient funds!" << endl;
                return;
            }
        }
    }
    cout << "Account not found!" << endl;
}

void accountInfo(Account accounts[], int numAccounts) {

    // Get the account number to display information about
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    // Find the account
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printAccountInfo(accounts[i]);
            return;
        }
    }

    cout << "Account not found!" << endl;
}

void printAllAccounts(Account accounts[], int numAccounts) {

    for (int i = 0; i < numAccounts; i++) {
        printAccountInfo(accounts[i]);
    }
}

void printAccountInfo(Account& account) {

    cout << "\nAccount number: " << account.accountNumber << endl;
    cout << "First name: " << account.firstName << endl;
    cout << "Last name: " << account.lastName << endl;
    cout << "Address: " << account.address << endl;
    cout << "Phone number: " << account.phoneNo << endl;
    cout << "Balance: " << account.balance << endl;
    cout << "Date of birth: " << account.dateOfBirth.day << "/" << account.dateOfBirth.month << "/" << account.dateOfBirth.year << endl;

}

void searchForAccount(Account accounts[], int numAccounts) {

    // Get the search criteria
    int searchOption = 0;

    cout << "Enter search option." << endl;
    cout << "1: Last name." << endl;
    cout << "2: Phone number." << endl;
    cout << "3: Account number." << endl;

    while (searchOption != 1 && searchOption != 2) {

        cout << "Enter search option: ";
        cin >> searchOption;

        if (searchOption != 1 && searchOption != 2) {
            cerr << "Enter a valid search option!" << endl;
        }

    }
    
    string searchTerm;

    switch (searchOption)
    {
    case 1: 
        
        // Search for accounts matching the search term
        cout << "Enter last name: ";
        cin >> searchTerm;

        for (int i = 0; i < numAccounts; i++) {
            
            if (accounts[i].lastName == searchTerm) {
                printAccountInfo(accounts[i]);
            }
        
        }
        break;

    case 2:

        cout << "Enter phone number: ";
        cin >> searchTerm;

        for (int i = 0; i < numAccounts; i++) {

            if (accounts[i].phoneNo == searchTerm) {
                printAccountInfo(accounts[i]);
            }

        }
        break;

    case 3: 

        int searchTerm;
        // Search for accounts matching the search term

        cout << "Enter account number: ";
        cin >> searchTerm;

        for (int i = 0; i < numAccounts; i++) {

            if (accounts[i].accountNumber == searchTerm) {
                printAccountInfo(accounts[i]);
            }

        }
        break;

    default:
        break;
    }

}

bool isValidDate(const BirthDate& date) {

    // Check if the day, month, and year are within reasonable ranges.

    if (date.month < 1 || date.month > 12) {
        return false;
    }

    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check if the day is within a valid range for the given month
    if (date.day < 1 || date.day > daysInMonth[date.month]) {
        return false;
    }

    // Check if the year is within a reasonable range
    if (date.year < 1930 || date.year > 2008) {

        if (date.year > 2008) {
            cerr << "You are too young to own an account!" << endl;
        }
        else if (date.year < 1930) {
            cerr << "Just c'mon!";
        }

        return false;
    }
        
    return true;
}