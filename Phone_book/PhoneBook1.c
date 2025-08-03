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

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void addContact() {
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
    
    contacts[contactCount++] = newContact;
    printf("Контакт добавлен успешно!\n");
}

void displayContacts() {
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

void editContact() {
    if (contactCount == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }
    
    displayContacts();
    printf("Введите номер контакта для редактирования: ");
    int index;
    scanf("%d", &index);
    getchar(); // очистка буфера
    
    if (index < 1 || index > contactCount) {
        printf("Неверный номер контакта!\n");
        return;
    }
    
    index--;
    
    printf("Редактирование контакта (оставьте поле пустым, чтобы не изменять)\n");
    
    printf("Имя [%s]: ", contacts[index].firstName);
    char input[MAX_LENGTH];
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].firstName, input);
    
    printf("Фамилия [%s]: ", contacts[index].lastName);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].lastName, input);
    
    printf("Место работы [%s]: ", contacts[index].workplace);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].workplace, input);
    
    printf("Должность [%s]: ", contacts[index].position);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].position, input);
    
    printf("Телефон [%s]: ", contacts[index].phone);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].phone, input);
    
    printf("Email [%s]: ", contacts[index].email);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].email, input);
    
    printf("Соцсети [%s]: ", contacts[index].social);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].social, input);
    
    printf("Мессенджер [%s]: ", contacts[index].messenger);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(contacts[index].messenger, input);
    
    printf("Контакт успешно обновлен!\n");
}

void deleteContact() {
    if (contactCount == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }
    
    displayContacts();
    printf("Введите номер контакта для удаления: ");
    int index;
    scanf("%d", &index);
    getchar(); // очистка буфера
    
    if (index < 1 || index > contactCount) {
        printf("Неверный номер контакта!\n");
        return;
    }
    
    index--;
    
    for (int i = index; i < contactCount - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    
    contactCount--;
    printf("Контакт успешно удален!\n");
}

int main() {
    int choice;
    
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
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
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