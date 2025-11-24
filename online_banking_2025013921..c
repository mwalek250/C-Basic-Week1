include <stdio.h>
include <stdlib.h>
include <string.h>

define FILE_NAME "accounts.txt"

typedef struct {
    char fullname[50];
    char accountNumber[20];
    char password[20];
    double balance;
} Account;

Account loggedIn;  
int isLoggedIn = 0;

/******************** UTILITY FUNCTIONS ************************/

int accountExists(char *accNum) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return 0;

    Account acc;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%lf\n",
                  acc.fullname, acc.accountNumber, acc.password, &acc.balance) != EOF) {
        if (strcmp(acc.accountNumber, accNum) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

Account getAccount(char *accNum) {
    FILE *fp = fopen(FILE_NAME, "r");
    Account acc;

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%lf\n",
                  acc.fullname, acc.accountNumber, acc.password, &acc.balance) != EOF) {
        if (strcmp(acc.accountNumber, accNum) == 0) {
            fclose(fp);
            return acc;
        }
    }

    fclose(fp);
    return acc;
}

void updateAccount(Account acc) {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    Account a;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%lf\n",
                  a.fullname, a.accountNumber, a.password, &a.balance) != EOF) {
        if (strcmp(a.accountNumber, acc.accountNumber) == 0) {
            fprintf(temp, "%s|%s|%s|%.2lf\n",
                    acc.fullname, acc.accountNumber, acc.password, acc.balance);
        } else {
            fprintf(temp, "%s|%s|%s|%.2lf\n",
                    a.fullname, a.accountNumber, a.password, a.balance);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}

/******************** CORE FEATURES ************************/

int generateAccountNumber() {
    FILE *fp = fopen(FILE_NAME, "r");
    int num = 1000;
    Account acc;

    if (!fp) return 1001;

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%lf\n",
                  acc.fullname, acc.accountNumber, acc.password, &acc.balance) != EOF) {
        int x = atoi(acc.accountNumber);
        if (x > num) num = x;
    }

    fclose(fp);
    return num + 1;
}

void registerAccount() {
    FILE *fp = fopen(FILE_NAME, "a");
    Account acc;

    printf("Enter Full Name: ");
    getchar();
    fgets(acc.fullname, sizeof(acc.fullname), stdin);
    acc.fullname[strcspn(acc.fullname, "\n")] = 0;

    sprintf(acc.accountNumber, "%d", generateAccountNumber());
    printf("Generated Account Number: %s\n", acc.accountNumber);

    printf("Create Password: ");
    scanf("%s", acc.password);

    printf("Initial Deposit (K): ");
    scanf("%lf", &acc.balance);

    fprintf(fp, "%s|%s|%s|%.2lf\n",
            acc.fullname, acc.accountNumber, acc.password, acc.balance);

    fclose(fp);

    printf("\nAccount created successfully!\n");
}

void login() {
    char accNum[20], pass[20];

    printf("Enter Account Number: ");
    scanf("%s", accNum);

    printf("Enter Password: ");
    scanf("%s", pass);

    if (!accountExists(accNum)) {
        printf("Account does not exist.\n");
        return;
    }

    Account acc = getAccount(accNum);

    if (strcmp(acc.password, pass) == 0) {
        loggedIn = acc;
        isLoggedIn = 1;
        printf("\nLogin successful! Welcome, %s.\n", loggedIn.fullname);
    } else {
        printf("Incorrect password.\n");
    }
}

void logout() {
    isLoggedIn = 0;
    printf("Logged out successfully.\n");
}

void deposit() {
    double amount;

    printf("Enter deposit amount (K): ");
    scanf("%lf", &amount);

    loggedIn.balance += amount;
    updateAccount(loggedIn);

    printf("Deposit successful! New balance: K%.2lf\n", loggedIn.balance);
}

void withdraw() {
    double amount;

    printf("Enter withdrawal amount (K): ");
    scanf("%lf", &amount);

    if (amount > loggedIn.balance) {
        printf("Insufficient funds.\n");
        return;
    }

    loggedIn.balance -= amount;
    updateAccount(loggedIn);

    printf("Withdrawal successful! New balance: K%.2lf\n", loggedIn.balance);
}

void transfer() {
    char targetAcc[20];
    double amount;

    printf("Enter target account number: ");
    scanf("%s", targetAcc);

    if (!accountExists(targetAcc)) {
        printf("Recipient account does not exist.\n");
        return;
    }

    printf("Enter amount to transfer (K): ");
    scanf("%lf", &amount);

    if (amount > loggedIn.balance) {
        printf("Insufficient balance.\n");
        return;
    }

    Account receiver = getAccount(targetAcc);

    loggedIn.balance -= amount;
    receiver.balance += amount;

    updateAccount(loggedIn);
    updateAccount(receiver);

    printf("Transfer successful!\n");
}

void changePassword() {
    char newPass[20];

    printf("Enter new password: ");
    scanf("%s", newPass);

    strcpy(loggedIn.password, newPass);
    updateAccount(loggedIn);

    printf("Password changed successfully.\n");
}

void displayDetails() {
    printf("\n===== ACCOUNT DETAILS =====\n");
    printf("Full Name: %s\n", loggedIn.fullname);
    printf("Account Number: %s\n", loggedIn.accountNumber);
    printf("Current Balance: K%.2lf\n", loggedIn.balance);
}

/******************** MENU ************************/

void menu() {
    int choice;

    while (1) {
        printf("\n===== ONLINE BANKING SYSTEM =====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        if (isLoggedIn) {
            printf("3. Deposit\n");
            printf("4. Withdraw\n");
            printf("5. Transfer\n");
            printf("6. Change Password\n");
            printf("7. Display Details\n");
            printf("8. Logout\n");
        }
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerAccount(); break;
            case 2: login(); break;
            case 3: if (isLoggedIn) deposit(); break;
            case 4: if (isLoggedIn) withdraw(); break;
            case 5: if (isLoggedIn) transfer(); break;
            case 6: if (isLoggedIn) changePassword(); break;
            case 7: if (isLoggedIn) displayDetails(); break;
            case 8: if (isLoggedIn) logout(); break;
            case 0: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
