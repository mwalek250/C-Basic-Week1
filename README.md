 Online Banking System (C Programming)

  Student Information
 Name: Kondwani Mwale
Student Number:2025013921

 Description
A menu-driven Online Banking System** implemented in C.  
Supports account registration, login/logout, deposit, withdrawal, fund transfer, password change, and account display.  
Balances are displayed in Zambian Kwacha (K)7 and data is stored persistently using `accounts.txt`.


 Features
1. Register a new bank account (with Student Name and Number)
2. Login system for authentication
3. Logout functionality
4. Deposit funds
5. Withdraw funds (balance validated)
6. Transfer funds between accounts
7. Change password securely
8. Display account details (password hidden)
9. Menu-driven interface using switch-case
10. Persistent storage using file handling

---

 How to Run
1. Install GCC compiler.
2. Copy `online_banking_2025013921.c` and `accounts.txt` into the same folder.
3. Open terminal in VS Code.
4. Compile:
   bash
   gcc online_banking_2025013921.c -o bank
