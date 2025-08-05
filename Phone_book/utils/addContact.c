#include "../PhoneBook1.h"

void addContact(Contact *contacts, int *contactCount) {
    if (contactCount >= MAX_CONTACTS) {
        printf("Телефонная книга переполнена!\n");
        return;
    }

    Contact newContact;
    
    printf("Добавление нового контакта\n");
    
    printf("Введите имя (обязательно): ");
    fgets(newContact.firstName, MAX_LENGTH, stdin);
    newContact.firstName[strcspn(newContact.firstName, "\n")] = '\0';
    
    printf("Введите фамилию (обязательно): ");
    fgets(newContact.lastName, MAX_LENGTH, stdin);
    newContact.lastName[strcspn(newContact.lastName, "\n")] = '\0';
    
    printf("Введите место работы: ");
    fgets(newContact.workplace, MAX_LENGTH, stdin);
    newContact.workplace[strcspn(newContact.workplace, "\n")] = '\0';
    
    printf("Введите должность: ");
    fgets(newContact.position, MAX_LENGTH, stdin);
    newContact.position[strcspn(newContact.position, "\n")] = '\0';
    
    printf("Введите номер телефона: ");
    fgets(newContact.phone, MAX_LENGTH, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';
    
    printf("Введите email: ");
    fgets(newContact.email, MAX_LENGTH, stdin);
    newContact.email[strcspn(newContact.email, "\n")] = '\0';
    
    printf("Введите ссылку на соцсети: ");
    fgets(newContact.social, MAX_LENGTH, stdin);
    newContact.social[strcspn(newContact.social, "\n")] = '\0';
    
    printf("Введите профиль в мессенджере: ");
    fgets(newContact.messenger, MAX_LENGTH, stdin);
    newContact.messenger[strcspn(newContact.messenger, "\n")] = '\0';
    
    contacts[*contactCount++] = newContact;
    printf("Контакт добавлен успешно!\n");
}