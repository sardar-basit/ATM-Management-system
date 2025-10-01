🏧 ATM Management System (C++ & OOP)
A console-based Automated Teller Machine (ATM) management system developed in C++ using Object-Oriented Programming (OOP) principles. This project simulates core ATM functionalities such as deposits, withdrawals, balance inquiries, and user authentication.

✨ Features
This system provides the following functionalities to the user:

User Authentication: Secure PIN-based login for existing users.

Balance Inquiry: Check the current account balance.

Cash Withdrawal: Withdraw funds with validation against the account balance.

Cash Deposit: Deposit funds into the account.

View Account Details: Display the user's name, account number, and current balance.

OOP Design: The system is structured using classes to represent real-world entities (like Account and ATM), demonstrating encapsulation, inheritance (if applicable), and clear separation of concerns.

🛠️ Technology Stack
Primary Language: C++

Paradigm: Object-Oriented Programming (OOP)

Environment: Console Application

🚀 Getting Started
Follow these steps to clone the repository and run the ATM simulator on your local machine.

Prerequisites
You must have a C++ compiler installed on your system. We recommend using one of the following:

g++ (GNU Compiler Collection, common on Linux/macOS and available via MinGW/Cygwin on Windows)

Clang (often used on macOS)

Visual Studio (C++ Build Tools on Windows)

Compilation and Execution
Clone the Repository:

git clone https://github.com/sardar-basit/ATM-Management-system.git

Navigate to the Project Directory:

cd ATM-Management-system

Compile the C++ Code:
Assuming your main source file is main.cpp (or similar), use your compiler to generate an executable.

Example using g++:

g++ *.cpp -o atm_system

(This command compiles all .cpp files in the directory and creates an executable file named atm_system.)

Run the System:
Execute the compiled program from your terminal:

On Linux/macOS:

./atm_system

On Windows (Command Prompt/PowerShell):

.\atm_system.exe

You will be presented with the main ATM menu in the console.

📂 Project Structure
The project is organized with clear responsibilities for each file (assuming standard OOP structure):

main.cpp: Entry point of the application, handles the primary menu loop and user interaction.

Account.h / Account.cpp: Class definition and implementation for handling individual bank accounts.

ATM.h / ATM.cpp: Class definition and implementation for managing the overall ATM logic, including authentication and transaction processing.

Other header/source files as needed.

🤝 How to Contribute
Contributions are welcome! If you find a bug or have an idea for an enhancement (like adding transaction history or multiple user profiles), feel free to:

Fork the repository.

Create a new feature branch (git checkout -b feature/new-feature).

Commit your changes (git commit -m 'Add: amazing new feature').

Push to the branch (git push origin feature/new-feature).

Open a Pull Request.

🧑‍💻 Author
Sardar Basit - https://github.com/sardar-basit
