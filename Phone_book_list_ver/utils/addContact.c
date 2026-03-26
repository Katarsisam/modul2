#include "../PhoneBook1.h"


void addContact(ContactList* list) {
    if (list->count >= MAX_CONTACTS) {
        printf("Телефонная книга переполнена!\n");
        return;
    }

    ContactNode* newNode = createContactNode();
    if (!newNode) return;

    printf("\nДобавление нового контакта\n");

    printf("Введите имя (обязательно): ");
    fgets(newNode->firstName, MAX_LENGTH, stdin);
    newNode->firstName[strcspn(newNode->firstName, "\n")] = '\0';

    printf("Введите фамилию (обязательно): ");
    fgets(newNode->lastName, MAX_LENGTH, stdin);
    newNode->lastName[strcspn(newNode->lastName, "\n")] = '\0';

    printf("Введите место работы: ");
    fgets(newNode->workplace, MAX_LENGTH, stdin);
    newNode->workplace[strcspn(newNode->workplace, "\n")] = '\0';

    printf("Введите должность: ");
    fgets(newNode->position, MAX_LENGTH, stdin);
    newNode->position[strcspn(newNode->position, "\n")] = '\0';

    printf("Введите номер телефона: ");
    fgets(newNode->phone, MAX_LENGTH, stdin);
    newNode->phone[strcspn(newNode->phone, "\n")] = '\0';

    printf("Введите email: ");
    fgets(newNode->email, MAX_LENGTH, stdin);
    newNode->email[strcspn(newNode->email, "\n")] = '\0';

    printf("Введите ссылку на соцсети: ");
    fgets(newNode->social, MAX_LENGTH, stdin);
    newNode->social[strcspn(newNode->social, "\n")] = '\0';

    printf("Введите профиль в мессенджере: ");
    fgets(newNode->messenger, MAX_LENGTH, stdin);
    newNode->messenger[strcspn(newNode->messenger, "\n")] = '\0';

    // Вставка с сохранением упорядоченности (по фамилии, затем по имени)
    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        ContactNode* current = list->head;
        while (current && compareContacts(newNode, current) > 0) {
            current = current->next;
        }

        if (current == NULL) {  // в конец
            newNode->prev = list->tail;
            list->tail->next = newNode;
            list->tail = newNode;
        } else if (current == list->head) {  // в начало
            newNode->next = list->head;
            list->head->prev = newNode;
            list->head = newNode;
        } else {  // в середину
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }

    list->count++;
    printf("Контакт добавлен успешно!\n");
}