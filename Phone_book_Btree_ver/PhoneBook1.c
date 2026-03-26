#include "PhoneBook1.h"

int main() {
    int choice;
    ContactTree phoneBook;
    initTree(&phoneBook);

    printf("=== Телефонная книга (задание 4.3 — бинарное дерево с балансировкой) ===\n\n");

    do {
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть все контакты\n");
        printf("3. Редактировать контакт\n");
        printf("4. Удалить контакт\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addContact(&phoneBook); break;
            case 2: displayContacts(&phoneBook); break;
            case 3: editContact(&phoneBook); break;
            case 4: deleteContact(&phoneBook); break;
            case 0: printf("Выход из программы...\n"); break;
            default: printf("Неверный выбор!\n");
        }
    } while (choice != 0);

    freeTree(&phoneBook);
    return 0;
}