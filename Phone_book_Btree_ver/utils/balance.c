#include "../PhoneBook1.h"

void balanceTree(ContactTree* tree) {
    if (tree->operations_since_balance < BALANCE_THRESHOLD) return;
    if (tree->count == 0) return;

    ContactNode** array = (ContactNode**)malloc(tree->count * sizeof(ContactNode*));
    if (!array) return;

    int index = 0;
    treeToArray(tree->root, array, &index);

    tree->root = arrayToBalancedBST(array, 0, tree->count - 1);
    free(array);

    tree->operations_since_balance = 0;
    printf("Дерево автоматически сбалансировано (%d контактов).\n", tree->count);
}

void treeToArray(ContactNode* node, ContactNode** array, int* index) {
    if (node == NULL) return;
    treeToArray(node->left, array, index);
    array[(*index)++] = node;
    treeToArray(node->right, array, index);
}

ContactNode* arrayToBalancedBST(ContactNode** array, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    ContactNode* node = array[mid];

    node->left = arrayToBalancedBST(array, start, mid - 1);
    node->right = arrayToBalancedBST(array, mid + 1, end);

    return node;
}