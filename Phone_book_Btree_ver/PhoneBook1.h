#ifndef PHONE_H
#define PHONE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_CONTACTS 100
#define BALANCE_THRESHOLD 10
#define MAX_STACK_SIZE 1000     // Максимальный размер стека для освобождения дерева

typedef struct ContactNode {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char workplace[MAX_LENGTH];
    char position[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char email[MAX_LENGTH];
    char social[MAX_LENGTH];
    char messenger[MAX_LENGTH];

    struct ContactNode* left;
    struct ContactNode* right;
} ContactNode;

typedef struct {
    ContactNode* root;
    int count;
    int operations_since_balance;
} ContactTree;

/* Основные функции */
void initTree(ContactTree* tree);
ContactNode* createContactNode(void);
int compareContacts(ContactNode* a, ContactNode* b);

void addContact(ContactTree* tree);
void displayContacts(ContactTree* tree);
void editContact(ContactTree* tree);
void deleteContact(ContactTree* tree);
void freeTree(ContactTree* tree);

/* Функции балансировки */
void balanceTree(ContactTree* tree);
void treeToArray(ContactNode* node, ContactNode** array, int* index);
ContactNode* arrayToBalancedBST(ContactNode** array, int start, int end);

#endif