#include "../PhoneBook1.h"

void initTree(ContactTree* tree) {
    tree->root = NULL;
    tree->count = 0;
    tree->operations_since_balance = 0;
}

ContactNode* createContactNode(void) {
    ContactNode* newNode = (ContactNode*)malloc(sizeof(ContactNode));
    if (!newNode) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int compareContacts(ContactNode* a, ContactNode* b) {
    int res = strcmp(a->lastName, b->lastName);
    if (res == 0) {
        res = strcmp(a->firstName, b->firstName);
    }
    return res;
}

void freeTree(ContactTree* tree) {
    if (tree->root == NULL) {
        printf("Дерево уже пусто.\n");
        return;
    }

    // Рекурсивное освобождение с использованием стека (итеративно)
    ContactNode* stack[MAX_STACK_SIZE];
    int top = 0;

    if (tree->root) {
        stack[top++] = tree->root;
    }

    while (top > 0) {
        ContactNode* node = stack[--top];

        if (node->left) {
            if (top >= MAX_STACK_SIZE) {
                printf("Предупреждение: стек переполнен при освобождении!\n");
                break;
            }
            stack[top++] = node->left;
        }
        if (node->right) {
            if (top >= MAX_STACK_SIZE) {
                printf("Предупреждение: стек переполнен при освобождении!\n");
                break;
            }
            stack[top++] = node->right;
        }

        free(node);
    }

    tree->root = NULL;
    tree->count = 0;
    tree->operations_since_balance = 0;
    printf("Память дерева успешно освобождена.\n");
}