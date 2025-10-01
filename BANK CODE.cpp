#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Base Account Class 
class Account {
protected:
    char name[50];
    int accNo;
    int pin;
    float balance;

public:
   Account() : accNo(0), pin(0), balance(0.0f)   
    {
        name[0] = '\0';         
    }

    virtual void createAccount() {
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name,50);
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Set 4-digit PIN: ";
        cin >> pin;
        while (pin < 1000 || pin > 9999) {
            cout << "Invalid PIN. Try again: ";
            cin >> pin;
        }
        cout << "Enter Initial Balance: ";
        cin >> balance;
        if (balance < 0) 
			balance = 0;
    }

    int getAccNo() const 
	{ 
		return accNo; 
	}
    float getBalance() const 
	{ 
		return balance; 
	}

    bool matchAccount(int acc) 
	{ 
		return accNo == acc; 
	}
    bool verifyPIN(int p) 
	{ 
		return pin == p; 
	}

    virtual void display() 
	{
        cout << "\nName: " << name;
        cout << "\nAccount Number: " << accNo;
        cout << "\nBalance: " << fixed << setprecision(2) << balance << "\n";
    }

    template<typename T>
    void deposit(T amount) 
	{
        if (amount > 0)
            balance += amount;
    }

    template<typename T>
    void withdraw(T amount)
	{
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Invalid or Insufficient Balance.\n";
    }
    float operator+(Account a)
    {
    	return balance+a.balance;
	}

};

void add_balance(bool isSavings)
{
	system("cls");
	ifstream fin(isSavings ? "savings.dat" : "current.dat", ios::binary);
    if (!fin) {
        cout << "No account file found.\n";
        return;
    }
	int a1,a2;
	bool found1=false,found2=false;
	cout<<"\n Enter the 1st Account Number";
	cin>>a1;
	cout<<"\n Enter the 2nd Account Number";
	cin>>a2;
	
	Account acc1,acc2,acc3;
	while(fin.read((char*)&acc3,sizeof(acc3)))
	{
		if(acc3.matchAccount(a1))
		{
			acc1=acc3;
			found1=true;	
		}
		if(acc3.matchAccount(a2))
		{
			acc2=acc3;
			found2=true;
		}		
	}
	 fin.close();

    if (!found1 || !found2) {
        cout << "One or both accounts not found.\n";
        return;
    } 
	
	float sum = acc1 + acc2;   
    cout << "/n Combined Balance of account"<<a1<<" and "<<a2<< " is: "<<setprecision(2)<<sum<< '\n';

}

// SavingsAccount
class SavingsAccount : public Account {
public:
    void display()  {
        cout << "\n--- Savings Account ---";
        Account::display();
    }
};

// CurrentAccount 
class CurrentAccount : public Account {
public:
    void display()  {
        cout << "\n--- Current Account ---";
        Account::display();
    }
};

//  Create Account 
void createAndSaveAccount(bool isSavings) {
	system("cls");
    ofstream fout(isSavings ? "savings.dat" : "current.dat", ios::binary | ios::app);

    if (!fout) {
        cout << "Error opening file.\n";
        return;
    }

    if (isSavings) {
        SavingsAccount acc;
        acc.createAccount();
        fout.write((char*)&acc, sizeof(acc));
    } 
	else {
        CurrentAccount acc;
        acc.createAccount();
        fout.write((char*)&acc, sizeof(acc));
    }

    fout.close();
    cout << "Account created successfully.\n";
}

//  Show All Accounts 
void showAllAccounts(bool isSavings) {
	system("cls");
    ifstream fin(isSavings ? "savings.dat" : "current.dat", ios::binary);
    if (!fin) {
        cout << "No account file found.\n";
        return;
    }

    Account acc;
    while (fin.read((char*)&acc, sizeof(acc))) {
        acc.display();
    }

    fin.close();
}


//  Deposit 
void depositToAccount(bool isSavings) {
	system("cls");
    fstream file(isSavings ? "savings.dat" : "current.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    int accNum, p;
    float amt;
    cout << "Enter Account Number: ";
    cin >> accNum;

    Account acc;
    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.matchAccount(accNum)) {
            cout << "Enter PIN: ";
            cin >> p;
            if (acc.verifyPIN(p)) {
                cout << "Enter amount to deposit: ";
                cin >> amt;
                acc.deposit(amt);
                int pos = file.tellg();
                file.seekp(pos - sizeof(acc));
                file.write((char*)&acc, sizeof(acc));
                cout << "Deposit successful.\n";
                file.close();
                return;
            } 
			else {
                cout << "Wrong PIN.\n";
                file.close();
                return;
            }
        }
    }

    cout << "Account not found.\n";
    file.close();
}

//  Withdraw 
void withdrawFromAccount(bool isSavings) {
	system("cls");
    fstream file(isSavings ? "savings.dat" : "current.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    int accNum, p;
    float amt;
    cout << "Enter Account Number: ";
    cin >> accNum;

    Account acc;
    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.matchAccount(accNum)) {
            cout << "Enter PIN: ";
            cin >> p;
            if (acc.verifyPIN(p)) {
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                acc.withdraw(amt);
                int pos = file.tellg();
                file.seekp(pos - sizeof(acc));
                file.write((char*)&acc, sizeof(acc));
                cout << "Withdrawal successful.\n";
                file.close();
                return;
            } 
			else {
                cout << "Wrong PIN.\n";
                file.close();
                return;
            }
        }
    }

    cout << "Account not found.\n";
    file.close();
}

//  Delete Account 
void deleteAccount(bool isSavings) {
	system("cls");
    ifstream fin(isSavings ? "savings.dat" : "current.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);

    if (!fin || !fout) {
        cout << "File error.\n";
        return;
    }

    int accNum, p;
    bool deleted = false;
    cout << "Enter Account Number to delete: ";
    cin >> accNum;

    Account acc;
    while (fin.read((char*)&acc, sizeof(acc))) {
        if (acc.matchAccount(accNum)) {
            cout << "Enter PIN: ";
            cin >> p;
            if (acc.verifyPIN(p)) {
                deleted = true;
                cout << "Account deleted.\n";
                continue;
            } 
			else {
                cout << "Wrong PIN. Account not deleted.\n";
                fout.write((char*)&acc, sizeof(acc));
            }
        } 
		else {
            fout.write((char*)&acc, sizeof(acc));
        }
    }
    fin.close();
    fout.close();

    remove(isSavings ? "savings.dat" : "current.dat");
    rename("temp.dat", isSavings ? "savings.dat" : "current.dat");

    if (!deleted)
        cout << "Account not found.\n";
}

//  Transfer 
void transferBetweenAccounts(bool isSavings) {
	system("cls");
    fstream file(isSavings ? "savings.dat" : "current.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    int fromAcc, toAcc, pin;
    float amount;
    cout << "Enter your Account Number: ";
    cin >> fromAcc;
    cout << "Enter PIN: ";
    cin >> pin;
    cout << "Enter recipient Account Number: ";
    cin >> toAcc;
    cout << "Enter amount to transfer: ";
    cin >> amount;

    Account accList[100];
    int count = 0;
    bool foundFrom = false, foundTo = false;

    while (file.read((char*)&accList[count], sizeof(Account))) {
        count++;
    }
    file.close();

    for (int i = 0; i < count; i++) {
        if (accList[i].matchAccount(fromAcc)) {
            if (!accList[i].verifyPIN(pin)) {
                cout << "Wrong PIN.\n";
                return;
            }
            if (accList[i].getBalance() < amount) {
                cout << "Insufficient balance.\n";
                return;
            }
            accList[i].withdraw(amount);
            foundFrom = true;
        }
        if (accList[i].matchAccount(toAcc)) {
            accList[i].deposit(amount);
            foundTo = true;
        }
    }

    if (!foundFrom || !foundTo) {
        cout << "Account(s) not found.\n";
        return;
    }

    ofstream fout(isSavings ? "savings.dat" : "current.dat", ios::binary | ios::trunc);
    for (int i = 0; i < count; i++)
        fout.write((char*)&accList[i], sizeof(Account));
    fout.close();

    cout << "Transfer successful.\n";
}

//  Balance 
  
void showBalance(bool isSavings) {
    system("cls");
    ifstream fin(isSavings ? "savings.dat" : "current.dat", ios::binary);
    if (!fin) {
        cout << "Error opening file.\n";
        return;
    }

    int accNum, pin;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> pin;

    Account acc;
    bool found = false;

    while (fin.read((char*)&acc, sizeof(acc))) {
        if (acc.matchAccount(accNum)) {
            if (acc.verifyPIN(pin)) {
                cout << "\nYour Current Balance is: " << fixed << setprecision(2) << acc.getBalance() << endl;
            } else {
                cout << "Wrong PIN.\n";
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
    }

    fin.close();
}



void waitKey() {
    cout << "\nPress Enter to continue...";
    cin.ignore(); 
	cin.get();
}

// ------------------ Menu ------------------
void menu() {
    int choice;
        while (true) {
    	system("cls");
        cout << "\n====== BANK SYSTEM MENU ======\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Show Savings Accounts\n";
        cout << "4. Show Current Accounts\n";
        cout << "5. Deposit to Savings\n";
        cout << "6. Deposit to Current\n";
        cout << "7. Withdraw from Savings\n";
        cout << "8. Withdraw from Current\n";
        cout << "9. Delete Savings Account\n";
        cout << "10. Delete Current Account\n";
        cout << "11. Transfer Savings to Savings\n";
        cout << "12. Transfer Current to Current\n";
        cout << "13. Show Savings Account Balance\n";
        cout << "14. Show Current Account Balance\n";
        cout<<"15. Add Balance of Savings\n";
        cout<<"16. Add Balance of Current\n";
        cout << "17. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
				createAndSaveAccount(true); 
				break;
            case 2: 
				createAndSaveAccount(false); 
				break;
            case 3: 
				showAllAccounts(true);
				waitKey(); 
				break;
            case 4: 
				showAllAccounts(false);
				waitKey(); 
				break;
            case 5: 
				depositToAccount(true); 
				waitKey();
				break;
            case 6: 
				depositToAccount(false); 
				waitKey();
				break;
            case 7: 
				withdrawFromAccount(true); 
				waitKey();
				break;
            case 8: 
				withdrawFromAccount(false); 
				waitKey();
				break;
            case 9: 
				deleteAccount(true); 
				waitKey();
				break;
            case 10: 
				deleteAccount(false); 
				waitKey();
				break;
            case 11: 
				transferBetweenAccounts(true);
				waitKey(); 
				break;
            case 12: 
				transferBetweenAccounts(false); 
				waitKey();
				break;
            case 13:
                showBalance(true); 
                waitKey();
                break;
            case 14:
                showBalance(false); 
                waitKey();
                break;
            case 15:
            	add_balance(true);
            	waitKey();
            	break;
            case 16:
            	add_balance(false);
            	waitKey();
            	break;
            case 17:
                cout << "Goodbye!\n";
                return;
                
            default: 
				cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}

