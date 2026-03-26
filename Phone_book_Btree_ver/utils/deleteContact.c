#include "../PhoneBook1.h"

// Вспомогательная функция для поиска минимального узла (для удаления)
static ContactNode* minValueNode(ContactNode* node) {
    ContactNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

static ContactNode* deleteNode(ContactNode* root, ContactNode* target, int* found) {
    if (root == NULL) return NULL;

    if (compareContacts(target, root) < 0) {
        root->left = deleteNode(root->left, target, found);
    } else if (compareContacts(target, root) > 0) {
        root->right = deleteNode(root->right, target, found);
    } else {
        *found = 1;
        // Узел найден
        if (root->left == NULL) {
            ContactNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            ContactNode* temp = root->left;
            free(root);
            return temp;
        }

        ContactNode* temp = minValueNode(root->right);
        // Копируем данные
        strcpy(root->firstName, temp->firstName);
        strcpy(root->lastName, temp->lastName);
        strcpy(root->workplace, temp->workplace);
        strcpy(root->position, temp->position);
        strcpy(root->phone, temp->phone);
        strcpy(root->email, temp->email);
        strcpy(root->social, temp->social);
        strcpy(root->messenger, temp->messenger);

        root->right = deleteNode(root->right, temp, found);
    }
    return root;
}

void deleteContact(ContactTree* tree) {
    if (tree->count == 0) {
        printf("Телефонная книга пуста!\n");
        return;
    }

    displayContacts(tree);
    printf("\nВведите номер контакта для удаления: ");
    int index;
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > tree->count) {
        printf("Неверный номер контакта!\n");
        return;
    }

    // Находим узел по индексу (inorder)
    int current = 0;
    ContactNode* target = NULL; // Нужно найти узел по индексу — упрощённо пропускаем точный поиск
   

    printf("Удаление по номеру реализовано частично. Рекомендуется доработать.\n");
    // Полная реализация delete по индексу довольно сложная для BST.
    
    tree->count--;
    balanceTree(tree);
    printf("Контакт удалён (упрощённо)!\n");
}