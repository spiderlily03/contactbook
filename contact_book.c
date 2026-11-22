#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "contacts.dat"

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

struct Contact c[MAX];
int n = 0;

void input(const char *msg, char *s, int size) {
    printf("%s", msg);
    fgets(s, size, stdin);
    s[strcspn(s, "\n")] = 0;
}

void load() {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) return;
    n = fread(c, sizeof(struct Contact), MAX, f);
    fclose(f);
}

void save() {
    FILE *f = fopen(FILE_NAME, "wb");
    fwrite(c, sizeof(struct Contact), n, f);
    fclose(f);
}

void add() {
    if (n == MAX) { printf("Contact book is full!\n"); return; }
    input("Name  : ", c[n].name, 50);
    input("Phone : ", c[n].phone, 15);
    input("Email : ", c[n].email, 50);
    n++;
    save();
    printf("Contact added.\n");
}

void display() {
    if (n == 0) { printf("No contacts.\n"); return; }
    printf("\n%-3s %-20s %-15s %s\n", "No", "Name", "Phone", "Email");
    for (int i = 0; i < n; i++)
        printf("%-3d %-20s %-15s %s\n", i + 1, c[i].name, c[i].phone, c[i].email);
}

int search() {
    char key[50];
    int found = 0;
    input("Enter name to search: ", key, 50);
    for (int i = 0; i < n; i++)
        if (strstr(c[i].name, key)) {
            printf("%d. %s | %s | %s\n", i + 1, c[i].name, c[i].phone, c[i].email);
            found = 1;
        }
    if (!found) printf("No match found.\n");
    return found;
}

void edit() {
    char t[10];
    display();
    input("Enter contact number to edit: ", t, 10);
    int i = atoi(t) - 1;
    if (i < 0 || i >= n) { printf("Invalid number.\n"); return; }
    input("New name  : ", c[i].name, 50);
    input("New phone : ", c[i].phone, 15);
    input("New email : ", c[i].email, 50);
    save();
    printf("Contact updated.\n");
}

void delete() {
    char t[10];
    display();
    input("Enter contact number to delete: ", t, 10);
    int i = atoi(t) - 1;
    if (i < 0 || i >= n) { printf("Invalid number.\n"); return; }
    for (; i < n - 1; i++) c[i] = c[i + 1];
    n--;
    save();
    printf("Contact deleted.\n");
}

int main() {
    char t[10];
    int ch;
    load();
    do {
        printf("\n--- CONTACT BOOK ---\n");
        printf("1. Add\n2. Display all\n3. Search\n4. Edit\n5. Delete\n0. Exit\n");
        input("Choice: ", t, 10);
        ch = atoi(t);
        switch (ch) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: edit(); break;
            case 5: delete(); break;
            case 0: printf("Bye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 0);
    return 0;
}