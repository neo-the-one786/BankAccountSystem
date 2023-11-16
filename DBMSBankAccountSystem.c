#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <sqlite3.h>

typedef struct UserInfo {
    char username[50];
    char firstName[20];
    char lastName[20];
    char fatherName[20];
    char motherName[20];
    char address[50];
    char accountType[20];
    char adharNum[20];
    char phoneNumber[15];
    int dateOfBirth;
    int monthOfBirth;
    int yearOfBirth;
    char password[50];
} UserInfo;

UserInfo user;

typedef struct Transaction {
    char receiverUsername[50];
    char senderUsername[50];
    long int amount;
} Transaction;

void createUserAccount(void);
void processAccountCreation(sqlite3* db);
void displayAccountCreatedMessage(void);
void userLogin(sqlite3* db);
void loginSuccess(void);
void displayUserInfo(sqlite3* db, const char username[]);
void displayMenu(sqlite3* db, const char username[]);
void checkBalance(sqlite3* db, const char username[]);
void transferMoney(sqlite3* db);
void logout(void);

int main() {
    sqlite3* db;
    int choice;
    if (sqlite3_open("bank_database.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    char* createUsersTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "username TEXT UNIQUE NOT NULL,"
                                  "firstName TEXT NOT NULL,"
                                  "lastName TEXT NOT NULL,"
                                  "fatherName TEXT NOT NULL,"
                                  "motherName TEXT NOT NULL,"
                                  "address TEXT NOT NULL,"
                                  "accountType TEXT NOT NULL,"
                                  "adharNum TEXT NOT NULL,"
                                  "phoneNumber TEXT NOT NULL,"
                                  "dateOfBirth INTEGER NOT NULL,"
                                  "monthOfBirth INTEGER NOT NULL,"
                                  "yearOfBirth INTEGER NOT NULL,"
                                  "password TEXT NOT NULL);";
    if (sqlite3_exec(db, createUsersTableQuery, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create users table\n");
        sqlite3_close(db);
        return 1;
    }
    gotoXY(20, 3);
    printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
    gotoXY(18, 5);
    printf("**********************************");
    gotoXY(25, 7);
    printf("DEVELOPER-Divyanshu Mishra (an improvement on source code of GfG's Naman Kumar)");
    gotoXY(20, 10);
    printf("1.... CREATE A BANK ACCOUNT");
    gotoXY(20, 12);
    printf("2.... ALREADY A USER? SIGN IN");
    gotoXY(20, 14);
    printf("3.... EXIT\n\n");
    printf("\n\nENTER YOUR CHOICE..");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            system("cls");
            printf("\n\n USERNAME 50 CHARACTERS MAX!!");
            printf("\n\n PASSWORD 50 CHARACTERS MAX!!");
            createUserAccount();
            break;
        case 2:
            userLogin(db);
            break;
        case 3:
            sqlite3_close(db);
            exit(0);
    }
    sqlite3_close(db);
    return 0;
}
void createUserAccount(void) {
    char password[50];
    system("cls");
    printf("\n\n!!!!!CREATE ACCOUNT!!!!!");
    printf("\n\nFIRST NAME..");
    scanf("%s", user.firstName);
    printf("\n\n\nLAST NAME..");
    scanf("%s", user.lastName);
    printf("\n\nFATHER's NAME..");
    scanf("%s", user.fatherName);
    printf("\n\nMOTHER's NAME..");
    scanf("%s", user.motherName);
    printf("\n\nADDRESS..");
    scanf("%s", user.address);
    printf("\n\nACCOUNT TYPE");
    scanf("%s", user.accountType);
    printf("\n\nDATE OF BIRTH..");
    printf("\nDATE-");
    scanf("%d", &user.dateOfBirth);
    printf("\nMONTH-");
    scanf("%d", &user.monthOfBirth);
    printf("\nYEAR-");
    scanf("%d", &user.yearOfBirth);
    printf("\n\nADHAR NUMBER");
    scanf("%s", user.adharNum);
    printf("\n\nPHONE NUMBER");
    scanf("%s", user.phoneNumber);
    printf("\n\nUSERNAME.. ");
    scanf("%s", user.username);
    printf("\n\nPASSWORD..");
    for (int i = 0; i < 50; i++) {
        char ch = getch();
        if (ch != 13) {
            password[i] = ch;
            ch = '*';
            printf("%c", ch);
        } else {
            break;
        }
    }
    strcpy(user.password, password);
    sqlite3* db;
    if (sqlite3_open("bank_database.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    processAccountCreation(db);
    sqlite3_close(db);
}
void processAccountCreation(sqlite3* db) {
    char insertUserQuery[200];
    sprintf(insertUserQuery, "INSERT INTO users (username, firstName, lastName, fatherName, motherName, "
                             "address, accountType, adharNum, phoneNumber, dateOfBirth, monthOfBirth, yearOfBirth, password) "
                             "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, %d, %d, '%s');",
            user.username, user.firstName, user.lastName, user.fatherName, user.motherName,
            user.address, user.accountType, user.adharNum, user.phoneNumber,
            user.dateOfBirth, user.monthOfBirth, user.yearOfBirth, user.password);
    if (sqlite3_exec(db, insertUserQuery, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to insert user into the database\n");
    }

    displayAccountCreatedMessage();
}


void checkBalance(sqlite3* db, const char username[]) {
    system("cls");
    displayUserInfo(db, username);
}

void transferMoney(sqlite3* db) {
    system("cls");
    char senderUsername[50];
    char receiverUsername[50];
    Transaction transaction;
    printf("---- TRANSFER MONEY ----");
    printf("========================");
    printf("FROM (your username).. ");
    scanf("%s", senderUsername);
    printf(" TO (username of person)..");
    scanf("%s", receiverUsername);
    char insertTransactionQuery[150];
    sprintf(insertTransactionQuery, "INSERT INTO transactions (senderUsername, receiverUsername, amount) "
                                    "VALUES ('%s', '%s', %ld);", senderUsername, receiverUsername, transaction.amount);
    if (sqlite3_exec(db, insertTransactionQuery, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to insert transaction into the database\n");
    }
    printf("AMOUNT SUCCESSFULLY TRANSFERRED....");
    getch();
    displayUserInfo(db, senderUsername);
}

void logout(void) {
    int i, j;
    system("cls");
    printf("Please wait, logging out");

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }
    printf("Sign out successfully..\n");
    printf("Press any key to continue..");
    getch();
}