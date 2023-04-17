/* APOLLO PROJECT
    MEMBERS:
    - Daquillana, Lue.
    - Dionisio, Jarred.
    - Jimenez, Nicole Andrei.
*/

// HEADER FILES
#include <stdio.h>
#include <stdlib.h>

// VARIABLES
#define USERNAME "user"
#define PASSWORD "pass"

// NEW DATA TYPE
typedef struct items {
    char product_code[20];
    char product_name[20];
    int price;
    int quantity;
} ITEM;

ITEM item;

// Checks if the product code is available.
int isProdCodeAvail(char code[]) {
    FILE *file;
    file = fopen("Inventory.txt", "r");
    while (!feof(file)) {
        fread(&item, sizeof(item), 1, file);
        int i = 0;
        while (code[i] != '\0' && item.product_code[i] != '\0') {
            if (code[i] != item.product_code[i]) {
                break;
            }
            i++;
        } if (code[i] == '\0' && item.product_code[i] == '\0') {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Checks if the input is an integer.
int getinteger(int input) {
    int result = scanf("%d", &input);
    while (result != 1 || input <= 0) {
        if (result != 1) {
            scanf("%*[^\n]");
        }
        printf("\n You've entered an invalid input.");
        printf("Please try again: ");
        result = scanf("%d", &input);
    }
    return input;
}

// ADD ITEMS
// Creates a new item in the data file.
void addItem() {
    printf("Add Item: \n");

    FILE *file;
    char code[20];
    char x[4] = {0};
    int a, code_length = 0;
    file = fopen("Inventory.txt", "ab");

    printf("\nEnter \"end\" to exit.");

    printf("\nEnter Product code: ");
    scanf("%s", code);

    while (code[code_length] != '\0') {
        code_length++;
    } if (code[0] == 'e' && code[1] == 'n' && code[2] == 'd' && code[3] == '\0') {
        printf("\nReturning to options...\n");
        void options();
        return;
    }

    int available = isProdCodeAvail(code);
    if (available) {
        printf("\n* Product is already in the inventory.\n");
        fclose(file);
        system("pause");
        system("cls");
        return;
    } for (int i = 0; i < code_length; i++) {
        item.product_code[i] = code[i];
    } item.product_code[code_length] = '\0';

    printf("Enter Product Name: ");
    scanf("%s", item.product_name);

    printf("Enter Product price: ");
    item.price = getinteger(item.price);

    printf("Enter Quantity: ");
    item.quantity = getinteger(item.quantity);

    fwrite(&item, sizeof(item), 1, file);
    fclose(file);

    int choice;
    printf("\nEnter 1 to add another item or any other integer to return to options: ");
    scanf("%d", &choice);

    if (choice == 1) {
        addItem();
    } else {
            printf("\nReturning to options...\n");
            system("cls");
            void options();
            return;
    }
}

// . . .
void options();

// LOGIN INTERFACE
int main() {
    printf("\tLOGIN:\n");
    printf("************************\n");
    char username[15], password[10];

    while (1) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        int username_valid = 1;
        int password_valid = 1;

        for (int i = 0; username[i] != '\0' || USERNAME[i] != '\0'; i++) {
            if (username[i] != USERNAME[i]) {
                username_valid = 0;
                break;
            }
        } for (int i = 0; password[i] != '\0' || PASSWORD[i] != '\0'; i++) {
            if (password[i] != PASSWORD[i]) {
                password_valid = 0;
                break;
            }
        } if (username_valid && password_valid) {
            printf("\nLogin successful!!\n");
            system("cls");
            options();
        } else {
            printf("\nSorry, you entered the wrong information.\n");
            printf("Please try again.\n\n");
        }
    }
    return 0;
}

// MENU INTERFACE
void options() {
    printf("\nPRODUCT MANAGEMENT SYSTEM\n");

    int num, choice;
    while (1) {
        printf("\n 1. Insert Items");
        printf("\n 2. Display Items");
        printf("\n 3. Update Inventory");
        printf("\n 4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");

        if (choice == 1) {
            addItem();
        } else {
            printf("Invalid choice.\n");
        }
    }
}
