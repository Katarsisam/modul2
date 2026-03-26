#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_CONTACTS 100
typedef struct ContactNode {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char workplace[MAX_LENGTH];
    char position[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char email[MAX_LENGTH];
    char social[MAX_LENGTH];
    char messenger[MAX_LENGTH];
    
    struct ContactNode* prev;
    struct ContactNode* next;
} ContactNode;

typedef struct {
    ContactNode* head;
    ContactNode* tail;
    int count;
} ContactList;

void initList(ContactList* list);
ContactNode* createContactNode();
void addContact(ContactList* list);
void displayContacts(ContactList* list);
void editContact(ContactList* list);
void deleteContact(ContactList* list);
void freeList(ContactList* list);

#endif