#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} Account;

int readAccountsFromFile(char *filename, Account accounts[], int *count) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        *count = 0;
        return 0;
    }
    *count = fread(accounts, sizeof(Account), 100, file);
    fclose(file);
    return 1;
}

void writeAccountsToFile(char *filename, Account accounts[], int count) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(accounts, sizeof(Account), count, file);
        fclose(file);
    }
}

int isUsernameExists(Account accounts[], int count, char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerAccount(Account accounts[], int *count) {
    if (*count >= 100) {
        printf("Danh sach tai khoan da day.\n");
        return;
    }

    char username[50], password[50], confirmPassword[50];

    while (1) {
        printf("Nhap ten tai khoan: ");
        scanf("%s", username);
        if (isUsernameExists(accounts, *count, username)) {
            printf("Tai khoan da ton tai. Vui long nhap lai.\n");
        } else {
            break;
        }
    }

    printf("Nhap mat khau: ");
    scanf("%s", password);
    printf("Xac nhan lai mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Dang ky that bai.\n");
        return;
    }

    Account newAccount;
    strcpy(newAccount.username, username);
    strcpy(newAccount.password, password);
    accounts[*count] = newAccount;
    (*count)++;

    printf("Dang ky tai khoan thanh cong.\n");
}

void login(Account accounts[], int count) {
    char username[50], password[50];
    printf("Nhap ten tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong.\n");
            return;
        }
    }
    printf("Dang nhap that bai. Ten tai khoan hoac mat khau khong dung.\n");
}

int main() {
    Account accounts[100];
    int count = 0;
    char filename[] = "accounts.dat";

    readAccountsFromFile(filename, accounts, &count);

    while (1) {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(accounts, count);
                break;
            case 2:
                registerAccount(accounts, &count);
                writeAccountsToFile(filename, accounts, count);
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }
}

