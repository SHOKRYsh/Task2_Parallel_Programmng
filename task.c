// Shokry Mansour Shokry
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> 

struct User {
    char email[50];
    char password[50];
};

union UserData {
    bool isActive;
    int active;    
};

void registerUser() {
    struct User user;
    union UserData data;

    printf("Enter your email: ");
    scanf("%s", user.email);
    printf("Enter your password: ");
    scanf("%s", user.password);

    char activeInput[10];
    printf("Are you active? (1 or true for active, 0 or false for inactive) ");
    scanf("%s", activeInput);

    for (int i = 0; activeInput[i]; i++) {
        activeInput[i] = tolower(activeInput[i]);
    }

    if (strcmp(activeInput, "1") == 0 || strcmp(activeInput, "true") == 0) {
        data.active = 1;
    } else {
        data.active = 0;
    }

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening\n");
        return;
    }

    fprintf(file, "%s %s %d\n", user.email, user.password, data.active);
    fclose(file);
    printf("Registration successful\n");
}

int loginUser() {
    struct User user;
    union UserData data;

    printf("Enter your email: ");
    scanf("%s", user.email);
    printf("Enter your password: ");
    scanf("%s", user.password);

    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char savedEmail[50], savedPassword[50];
        int savedActive;
        sscanf(line, "%s %s %d", savedEmail, savedPassword, &savedActive);

        if (strcmp(user.email, savedEmail) == 0 && strcmp(user.password, savedPassword) == 0) {
            data.active = savedActive;
            fclose(file);

            if (data.active == 1) {
                printf("Login successful. User is active.\n");
            } else {
                printf("Login successful. User is inactive.\n");
            }
            return 1;
        }
    }

    fclose(file);
    printf("Login failed. Incorrect email or password\n");
    return 0;
}

int main() {
    int choice;
    printf("-----------------------------------------\n");
    printf("1. Register\n2. Login\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        registerUser();
    } else if (choice == 2) {
        loginUser();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
