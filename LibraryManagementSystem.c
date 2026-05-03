#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char name[50];
};

void addBook() {
    FILE *fp = fopen("library.txt", "a");
    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", b.name);

    fprintf(fp, "%d %s\n", b.id, b.name);
    fclose(fp);

    printf("Book added successfully!\n");
}

void viewBooks() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Book List ---\n");
    while (fscanf(fp, "%d %s", &b.id, b.name) != EOF) {
        printf("ID: %d  Name: %s\n", b.id, b.name);
    }

    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s", &b.id, b.name) != EOF) {
        if (b.id == id) {
            printf("Found -> ID: %d Name: %s\n", b.id, b.name);
            found = 1;
        }
    }

    if (!found) printf("Book not found!\n");

    fclose(fp);
}

void deleteBook() {
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s", &b.id, b.name) != EOF) {
        if (b.id != id) {
            fprintf(temp, "%d %s\n", b.id, b.name);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Library Menu =====\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
