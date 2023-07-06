#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Drug;

Drug drug_inventory[100];
int drug_count = 0;

void add_drug() {
    printf("Enter drug name: ");
    scanf("%s", drug_inventory[drug_count].name);
    printf("Enter price: ");
    scanf("%f", &drug_inventory[drug_count].price);
    printf("Enter quantity: ");
    scanf("%d", &drug_inventory[drug_count].quantity);
    drug_count++;
    printf("Drug added successfully!\n");
}

void update_drug() {
    char name[MAX_NAME_LENGTH];
    printf("Enter drug name: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < drug_count; i++) {
        if (strcmp(drug_inventory[i].name, name) == 0) {
            printf("Enter new price: ");
            scanf("%f", &drug_inventory[i].price);
            printf("Enter new quantity: ");
            scanf("%d", &drug_inventory[i].quantity);
            found = 1;
            printf("Drug information updated successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Drug not found in the inventory!\n");
    }
}

void view_drug() {
    char name[MAX_NAME_LENGTH];
    printf("Enter drug name (leave blank to view all drugs): ");
    scanf("%s", name);
    
    if (strcmp(name, "") == 0) {
        if (drug_count == 0) {
            printf("No drugs in the inventory!\n");
        } else {
            for (int i = 0; i < drug_count; i++) {
                printf("Drug Name: %s\n", drug_inventory[i].name);
                printf("Price: %.2f\n", drug_inventory[i].price);
                printf("Quantity: %d\n", drug_inventory[i].quantity);
            }
        }
    } else {
        int found = 0;
        for (int i = 0; i < drug_count; i++) {
            if (strcmp(drug_inventory[i].name, name) == 0) {
                printf("Drug Name: %s\n", drug_inventory[i].name);
                printf("Price: %.2f\n", drug_inventory[i].price);
                printf("Quantity: %d\n", drug_inventory[i].quantity);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Drug not found in the inventory!\n");
        }
    }
}

void record_purchase() {
    char name[MAX_NAME_LENGTH];
    printf("Enter drug name: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < drug_count; i++) {
        if (strcmp(drug_inventory[i].name, name) == 0) {
            int quantity;
            printf("Enter quantity purchased: ");
            scanf("%d", &quantity);
            
            if (quantity <= drug_inventory[i].quantity) {
                drug_inventory[i].quantity -= quantity;
                found = 1;
                printf("Purchase recorded successfully!\n");
            } else {
                printf("Insufficient quantity in the inventory!\n");
            }
            break;
        }
    }
    
    if (!found) {
        printf("Drug not found in the inventory!\n");
    }
}

void search_drug() {
    char keyword[MAX_NAME_LENGTH];
    printf("Enter a keyword to search for drugs: ");
    scanf("%s", keyword);
    
    int found = 0;
    for (int i = 0; i < drug_count; i++) {
        if (strstr(drug_inventory[i].name, keyword) != NULL) {
            printf("%s\n", drug_inventory[i].name);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No drugs found matching the keyword.\n");
    }
}

void delete_drug() {
    char name[MAX_NAME_LENGTH];
    printf("Enter drug name to delete: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < drug_count; i++) {
        if (strcmp(drug_inventory[i].name, name) == 0) {
            for (int j = i; j < drug_count - 1; j++) {
                drug_inventory[j] = drug_inventory[j + 1];
            }
            drug_count--;
            found = 1;
            printf("%s deleted from the inventory.\n", name);
            break;
        }
    }
    
    if (!found) {
        printf("Drug not found in the inventory!\n");
    }
}

void menu() {
    while (1) {
        printf("\nPharmacy Management System\n");
        printf("1. Add Drug\n");
        printf("2. Update Drug Information\n");
        printf("3. View Drug Information\n");
        printf("4. Record Purchase\n");
        printf("5. Search Drug\n");
        printf("6. Delete Drug\n");
        printf("7. Quit\n");
        
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_drug();
                break;
            case 2:
                update_drug();
                break;
            case 3:
                view_drug();
                break;
            case 4:
                record_purchase();
                break;
            case 5:
                search_drug();
                break;
            case 6:
                delete_drug();
                break;
            case 7:
                return;
            default:
                printf("Invalid choice. Try again!\n");
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}
