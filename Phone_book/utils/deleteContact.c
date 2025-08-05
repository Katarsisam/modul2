#include "../PhoneBook1.h"
void deleteContact(Contact *contacts, int *contactCount) {
    if (contactCount == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }
    
    displayContacts(contacts, contactCount);
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