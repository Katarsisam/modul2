#include "../PhoneBook1.h"

static void inorderTraversal(ContactNode* node, int* counter) {
    if (node == NULL) return;

    inorderTraversal(node->left, counter);

    printf("\nКонтакт #%d\n", (*counter)++);
    printf("Фамилия: %s\n", node->lastName);
    printf("Имя: %s\n", node->firstName);
    if (strlen(node->workplace)) printf("Место работы: %s\n", node->workplace);
    if (strlen(node->position))  printf("Должность: %s\n", node->position);
    if (strlen(node->phone))     printf("Телефон: %s\n", node->phone);
    if (strlen(node->email))     printf("Email: %s\n", node->email);
    if (strlen(node->social))    printf("Соцсети: %s\n", node->social);
    if (strlen(node->messenger)) printf("Мессенджер: %s\n", node->messenger);

    inorderTraversal(node->right, counter);
}

void displayContacts(ContactTree* tree) {
    if (tree->count == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }

    printf("\nСписок контактов (%d шт.):\n", tree->count);
    int counter = 1;
    inorderTraversal(tree->root, &counter);
}