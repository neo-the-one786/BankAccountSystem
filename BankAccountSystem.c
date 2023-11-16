#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

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

void gotoXY(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void createUserAccount(void);
void displayAccountCreatedMessage(void);
void userLogin(void);
void loginSuccess(void);
void displayUserInfo(const char username[]);
void displayMenu(const char username[]);
void checkBalance(const char username[]);
void transferMoney(void);
void logout(void);

int main() {
    int choice;
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
            userLogin();
            break;
        case 3:
            exit(0);
    }
    return 0;
}

void createUserAccount(void) {
    char password[50];
    FILE *filePointer = fopen("users.dat", "ab");
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
    fwrite(&user, sizeof(user), 1, filePointer);
    fclose(filePointer);
    displayAccountCreatedMessage();
}

void displayAccountCreatedMessage(void) {
    system("cls");
    printf("PLEASE WAIT....\n\nYOUR DATA IS PROCESSING....");
    for (int i = 0; i < 200000000; i++) {
        i++;
        i--;
    }
    gotoXY(30, 10);
    printf("ACCOUNT CREATED SUCCESSFULLY....");
    gotoXY(0, 20);
    printf("Press enter to login");

    getch();
    userLogin();
}

void userLogin(void) {
    system("cls");
    char username[50];
    char password[50];
    FILE *filePointer = fopen("users.dat", "rb");
    if (filePointer == NULL) {
        printf("ERROR IN OPENING FILE");
    }
    gotoXY(34, 2);
    printf(" ACCOUNT LOGIN ");
    gotoXY(7, 5);
    printf("***********************************************"
           "********************************");
    gotoXY(35, 10);
    printf("==== LOG IN ====");
    gotoXY(35, 12);
    printf("USERNAME.. ");
    scanf("%s", username);
    gotoXY(35, 14);
    printf("PASSWORD..");
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
    while (fread(&user, sizeof(user), 1, filePointer)) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            loginSuccess();
            displayUserInfo(username);
        }
    }
    fclose(filePointer);
}

void loginSuccess(void) {
    int i;
    FILE *filePointer = fopen("users.dat", "rb");
    system("cls");
    printf("Fetching account details.....\n");
    for (i = 0; i < 20000; i++) {
        i++;
        i--;
    }
    gotoXY(30, 10);
    printf("LOGIN SUCCESSFUL....");
    gotoXY(0, 20);
    printf("Press enter to continue");
    getch();
    fclose(filePointer);
}

void displayUserInfo(const char username[]) {
    system("cls");
    FILE *filePointer = fopen("users.dat", "rb");
    if (filePointer == NULL) {
        printf("error in opening file");
    }
    while (fread(&user, sizeof(user), 1, filePointer)) {
        if (strcmp(username, user.username) == 0) {
            gotoXY(30, 1);
            printf("WELCOME, %s %s", user.firstName, user.lastName);
            gotoXY(28, 2);
            printf("..........................");
            gotoXY(55, 6);
            printf("==== YOUR ACCOUNT INFO ====");
            gotoXY(55, 8);
            printf("***************************");
            gotoXY(55, 10);
            printf("NAME: %s %s", user.firstName, user.lastName);
            gotoXY(55, 12);
            printf("FATHER's NAME: %s", user.fatherName);
            gotoXY(55, 14);
            printf("MOTHER's NAME: %s", user.motherName);
            gotoXY(55, 16);
            printf("ADHAR CARD NUMBER: %s", user.adharNum);
            gotoXY(55, 18);
            printf("MOBILE NUMBER: %s", user.phoneNumber);
            gotoXY(55, 20);
            printf("DATE OF BIRTH: %d-%d-%d", user.dateOfBirth, user.monthOfBirth, user.yearOfBirth);
            gotoXY(55, 22);
            printf("ADDRESS: %s", user.address);
            gotoXY(55, 24);
            printf("ACCOUNT TYPE: %s", user.accountType);
        }
    }
    fclose(filePointer);
    displayMenu(username);
}

void displayMenu(const char username[]) {
    gotoXY(0, 6);
    printf(" HOME ");
    gotoXY(0, 7);
    printf("******");
    gotoXY(0, 9);
    printf(" 1....CHECK BALANCE");
    gotoXY(0, 11);
    printf(" 2....TRANSFER MONEY");
    gotoXY(0, 13);
    printf(" 3....LOG OUT\n\n");
    gotoXY(0, 15);
    printf(" 4....EXIT\n\n");
    printf(" ENTER YOUR CHOICES..");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            checkBalance(username);
            break;
        case 2:
            transferMoney();
            break;
        case 3:
            logout();
            userLogin();
            break;
        case 4:
            exit(0);
    }
}

void checkBalance(const char username[]) {
    system("cls");
    FILE *filePointer = fopen("transactions.dat", "rb");
    if (filePointer == NULL) {
        printf("Error in opening file");
    }
    fclose(filePointer);
    displayUserInfo(username);
}

void transferMoney(void) {
    system("cls");
    char senderUsername[50];
    char receiverUsername[50];
    Transaction transaction;
    FILE *userFile = fopen("users.dat", "rb");
    FILE *transactionFile = fopen("transactions.dat", "ab");
    gotoXY(33, 4);
    printf("---- TRANSFER MONEY ----");
    gotoXY(33, 5);
    printf("========================");
    gotoXY(33, 11);
    printf("FROM (your username).. ");
    scanf("%s", senderUsername);
    gotoXY(33, 13);
    printf(" TO (username of person)..");
    scanf("%s", receiverUsername);
    while (fread(&user, sizeof(user), 1, userFile)) {
        if (strcmp(receiverUsername, user.username) == 0) {
            strcpy(transaction.receiverUsername, user.username);
            strcpy(transaction.senderUsername, senderUsername);
        }
    }
    gotoXY(33, 16);
    printf("ENTER THE AMOUNT TO BE TRANSFERRED..");
    scanf("%ld", &transaction.amount);
    fwrite(&transaction, sizeof(transaction), 1, transactionFile);
    gotoXY(0, 26);
    printf(
            "--------------------------------------------------"
            "--------------------------------------------");
    gotoXY(0, 28);
    printf(
            "--------------------------------------------------"
            "--------------------------------------------");
    gotoXY(0, 29);
    printf("Transferring amount, Please wait..");
    gotoXY(10, 27);
    for (int i = 0; i < 70; i++) {
        for (int j = 0; j < 1200000; j++) {
            j++;
            j--;
        }
        printf("*");
    }
    gotoXY(33, 40);
    printf("AMOUNT SUCCESSFULLY TRANSFERRED....");
    getch();
    fclose(userFile);
    fclose(transactionFile);
    displayUserInfo(senderUsername);
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
    gotoXY(30, 10);
    printf("Sign out successfully..\n");
    gotoXY(0, 20);
    printf("Press any key to continue..");
    getch();
}