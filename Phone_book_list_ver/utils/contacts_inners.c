#include "../PhoneBook1.h"

void initList(ContactList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

ContactNode* createContactNode(void) {
    ContactNode* newNode = (ContactNode*)malloc(sizeof(ContactNode));
    if (!newNode) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

int compareContacts(ContactNode* a, ContactNode* b) {
    int res = strcmp(a->lastName, b->lastName);
    if (res == 0) {
        res = strcmp(a->firstName, b->firstName);
    }
    return res;
}

void freeList(ContactList* list) {
    ContactNode* current = list->head;
    while (current) {
        ContactNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = list->tail = NULL;
    list->count = 0;
}