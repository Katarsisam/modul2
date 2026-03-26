#include "../PhoneBook1.h"

void displayContacts(ContactList* list) {
    if (list->count == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }

    printf("\nСписок контактов (%d шт.):\n", list->count);
    ContactNode* current = list->head;
    int i = 1;

    while (current) {
        printf("\nКонтакт #%d\n", i++);
        printf("Фамилия: %s\n", current->lastName);
        printf("Имя: %s\n", current->firstName);
        if (strlen(current->workplace)) printf("Место работы: %s\n", current->workplace);
        if (strlen(current->position))  printf("Должность: %s\n", current->position);
        if (strlen(current->phone))     printf("Телефон: %s\n", current->phone);
        if (strlen(current->email))     printf("Email: %s\n", current->email);
        if (strlen(current->social))    printf("Соцсети: %s\n", current->social);
        if (strlen(current->messenger)) printf("Мессенджер: %s\n", current->messenger);

        current = current->next;
    }
}