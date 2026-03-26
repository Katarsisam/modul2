#include "../PhoneBook1.h"


void editContact(ContactList* list) {
    if (list->count == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }

    displayContacts(list);
    printf("\nВведите номер контакта для редактирования: ");
    int index;
    scanf("%d", &index);
    getchar();  // очистка буфера

    if (index < 1 || index > list->count) {
        printf("Неверный номер контакта!\n");
        return;
    }

    // Поиск нужного узла
    ContactNode* current = list->head;
    for (int i = 1; i < index; i++) {
        current = current->next;
    }

    printf("\nРедактирование контакта (оставьте поле пустым, чтобы не изменять):\n");

    char input[MAX_LENGTH];

    printf("Имя [%s]: ", current->firstName);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->firstName, input);

    printf("Фамилия [%s]: ", current->lastName);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->lastName, input);

    printf("Место работы [%s]: ", current->workplace);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->workplace, input);

    printf("Должность [%s]: ", current->position);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->position, input);

    printf("Телефон [%s]: ", current->phone);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->phone, input);

    printf("Email [%s]: ", current->email);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->email, input);

    printf("Соцсети [%s]: ", current->social);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->social, input);

    printf("Мессенджер [%s]: ", current->messenger);
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(current->messenger, input);

    printf("Контакт успешно обновлён!\n");
}