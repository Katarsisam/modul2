#include "../PhoneBook1.h"

void displayContacts(Contact *contacts, int *contactCount) {
    if (contactCount == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }
    
    printf("\nСписок контактов:\n");
    for (int i = 0; i < contactCount; i++) {
        printf("\nКонтакт #%d\n", i + 1);
        printf("Фамилия: %s\n", contacts[i].lastName);
        printf("Имя: %s\n", contacts[i].firstName);
        if (strlen(contacts[i].workplace)) printf("Место работы: %s\n", contacts[i].workplace);
        if (strlen(contacts[i].position)) printf("Должность: %s\n", contacts[i].position);
        if (strlen(contacts[i].phone)) printf("Телефон: %s\n", contacts[i].phone);
        if (strlen(contacts[i].email)) printf("Email: %s\n", contacts[i].email);
        if (strlen(contacts[i].social)) printf("Соцсети: %s\n", contacts[i].social);
        if (strlen(contacts[i].messenger)) printf("Мессенджер: %s\n", contacts[i].messenger);
    }
}