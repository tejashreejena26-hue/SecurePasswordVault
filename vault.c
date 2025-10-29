#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

#define MAX 100

struct Password {
    char site[50];
    char username[50];
    char password[50];
};

void addPassword();
void viewPasswords();
void deletePassword();

int main() {
    int choice;

    while (1) {
        printf("\n===== Secure Password Vault =====\n");
        printf("1. Add New Password\n");
        printf("2. View Saved Passwords\n");
        printf("3. Delete All Passwords\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            addPassword();
            break;
        case 2:
            viewPasswords();
            break;
        case 3:
            deletePassword();
            break;
        case 4:
            printf("Exiting vault...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

void addPassword() {
    FILE *fp = fopen("vault.txt", "a");
    struct Password p;
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter site name: ");
    fgets(p.site, sizeof(p.site), stdin);
    p.site[strcspn(p.site, "\n")] = '\0';

    printf("Enter username: ");
    fgets(p.username, sizeof(p.username), stdin);
    p.username[strcspn(p.username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(p.password, sizeof(p.password), stdin);
    p.password[strcspn(p.password, "\n")] = '\0';

    encrypt(p.password);

    fprintf(fp, "%s,%s,%s\n", p.site, p.username, p.password);
    fclose(fp);

    printf("✅ Password saved securely!\n");
}

void viewPasswords() {
    FILE *fp = fopen("vault.txt", "r");
    struct Password p;
    char line[200];
    if (!fp) {
        printf("No passwords found.\n");
        return;
    }

    printf("\n--- Stored Passwords ---\n");
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%49[^,],%49[^,],%49[^\n]", p.site, p.username, p.password);
        decrypt(p.password);
        printf("Site: %s\nUsername: %s\nPassword: %s\n\n", p.site, p.username, p.password);
    }
    fclose(fp);
}

void deletePassword() {
    FILE *fp = fopen("vault.txt", "w");
    if (fp) {
        fclose(fp);
        printf("All passwords deleted successfully!\n");
    } else {
        printf("Error deleting passwords!\n");
    }
}
