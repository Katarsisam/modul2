#ifndef PHONE_H
#define PHONE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 100
#define MAX_LENGTH 100

typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char workplace[MAX_LENGTH];
    char position[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char email[MAX_LENGTH];
    char social[MAX_LENGTH];
    char messenger[MAX_LENGTH];
} Contact;

void addContact(Contact *contacts, int *contactCount);
void displayContacts(Contact *contacts, int *contactCount);
void editContact(Contact *contacts, int *contactCount);
void deleteContact(Contact *contacts, int *contactCount);



#endif