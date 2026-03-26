#include "../PhoneBook1.h"

static ContactNode* insertNode(ContactNode* node, ContactNode* newNode) {
    if (node == NULL) return newNode;

    if (compareContacts(newNode, node) < 0) {
        node->left = insertNode(node->left, newNode);
    } else {
        node->right = insertNode(node->right, newNode);
    }
    return node;
}

void addContact(ContactTree* tree) {
    if (tree->count >= MAX_CONTACTS) {
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

    tree->root = insertNode(tree->root, newNode);
    tree->count++;
    tree->operations_since_balance++;

    balanceTree(tree);   // Периодическая балансировка

    printf("Контакт добавлен успешно!\n");
}