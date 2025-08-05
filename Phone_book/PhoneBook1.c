#include "PhoneBook1.h"



int main() {
    int choice;
    int contactCount = 0;
    Contact contacts[MAX_CONTACTS];
    do {
        printf("\nТелефонная книга\n");
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть все контакты\n");
        printf("3. Редактировать контакт\n");
        printf("4. Удалить контакт\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar(); // очистка буфера
        
        switch (choice) {
            case 1:
                addContact(contacts, contactCount);
                break;
            case 2:
                displayContacts(contacts, contactCount);
                break;
            case 3:
                editContact(contacts, contactCount);
                break;
            case 4:
                deleteContact(contacts, contactCount);
                break;
            case 0:
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 0);
    
    return 0;
}