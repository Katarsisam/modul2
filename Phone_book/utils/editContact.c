#include "../PhoneBook1.h"

void editContact(Contact *contacts, int *contactCount) {
    if (contactCount == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }
    
    displayContacts(contacts, contactCount);
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
