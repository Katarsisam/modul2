#include "../PhoneBook1.h"

void deleteContact(ContactList* list) {
    if (list->count == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }

    displayContacts(list);
    printf("\nВведите номер контакта для удаления: ");
    int index;
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > list->count) {
        printf("Неверный номер контакта!\n");
        return;
    }

    // Поиск узла
    ContactNode* current = list->head;
    for (int i = 1; i < index; i++) {
        current = current->next;
    }

    // Удаление из списка
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }

    free(current);
    list->count--;

    printf("Контакт успешно удалён!\n");
}