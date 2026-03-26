#include "../PhoneBook1.h"

static ContactNode* findNodeByIndex(ContactNode* node, int* current, int target) {
    if (node == NULL) return NULL;

    ContactNode* left = findNodeByIndex(node->left, current, target);
    if (left) return left;

    if (++(*current) == target) return node;

    return findNodeByIndex(node->right, current, target);
}

void editContact(ContactTree* tree) {
    if (tree->count == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }

    displayContacts(tree);
    printf("\nВведите номер контакта для редактирования: ");
    int index;
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > tree->count) {
        printf("Неверный номер контакта!\n");
        return;
    }

    int current = 0;
    ContactNode* target = findNodeByIndex(tree->root, &current, index);
    if (!target) return;

    char input[MAX_LENGTH];
    printf("\nРедактирование контакта (оставьте пустым для пропуска):\n");

    printf("Имя [%s]: ", target->firstName);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->firstName, input);

    printf("Фамилия [%s]: ", target->lastName);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->lastName, input);

    printf("Место работы [%s]: ", target->workplace);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->workplace, input);

    printf("Должность [%s]: ", target->position);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->position, input);

    printf("Телефон [%s]: ", target->phone);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->phone, input);

    printf("Email [%s]: ", target->email);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->email, input);

    printf("Соцсети [%s]: ", target->social);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->social, input);

    printf("Мессенджер [%s]: ", target->messenger);
    fgets(input, MAX_LENGTH, stdin); input[strcspn(input, "\n")] = '\0';
    if (strlen(input)) strcpy(target->messenger, input);

    printf("Контакт успешно обновлён!\n");
}