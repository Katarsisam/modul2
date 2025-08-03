#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRIORITY 255

// ��������� �������� �������
typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

// ��������� ������� � �����������
typedef struct {
    Node* front;
} PriorityQueue;

// ������������� �������
void initQueue(PriorityQueue* q) {
    q->front = NULL;
}

// ���������� �������� � ������� � �����������
void enqueue(PriorityQueue* q, int data, int priority) {
    if (priority < 0 || priority > MAX_PRIORITY) {
        printf("Invalid priority! Must be between 0 and %d\n", MAX_PRIORITY);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    // ���� ������� ����� ��� ����� ������� ����� ����� ������� ���������, ��� ������
    if (q->front == NULL || priority > q->front->priority) {
        newNode->next = q->front;
        q->front = newNode;
    } else {
        Node* current = q->front;
        // ������� ����� ��� �������
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// ���������� ������� �������� �� �������
int dequeueFront(PriorityQueue* q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1; // ��� ������ ��������, ������������ ������
    }

    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    free(temp);
    return data;
}

// ���������� �������� � ��������� �����������
int dequeueWithPriority(PriorityQueue* q, int priority) {
    if (priority < 0 || priority > MAX_PRIORITY) {
        printf("Invalid priority! Must be between 0 and %d\n", MAX_PRIORITY);
        return -1;
    }

    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    // ���� ������ ������� ����� ������ ���������
    if (q->front->priority == priority) {
        return dequeueFront(q);
    }

    Node* current = q->front;
    Node* prev = NULL;

    // ���� ������� � ������ �����������
    while (current != NULL && current->priority != priority) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("No element with priority %d found!\n", priority);
        return -1;
    }

    prev->next = current->next;
    int data = current->data;
    free(current);
    return data;
}

// ���������� �������� � ����������� �� ���� ���������
int dequeueWithMinPriority(PriorityQueue* q, int minPriority) {
    if (minPriority < 0 || minPriority > MAX_PRIORITY) {
        printf("Invalid priority! Must be between 0 and %d\n", MAX_PRIORITY);
        return -1;
    }

    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    // ���� ������ ������� ������������� �������
    if (q->front->priority >= minPriority) {
        return dequeueFront(q);
    }

    Node* current = q->front;
    Node* prev = NULL;

    // ���� ������ ������� � ���������� �����������
    while (current != NULL && current->priority < minPriority) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("No element with priority >= %d found!\n", minPriority);
        return -1;
    }

    // ���� ��� ������ ������� � �������
    if (prev == NULL) {
        q->front = current->next;
    } else {
        prev->next = current->next;
    }

    int data = current->data;
    free(current);
    return data;
}

// ������ ������� (��� �������)
void printQueue(PriorityQueue* q) {
    Node* current = q->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("[%d (prio %d)] ", current->data, current->priority);
        current = current->next;
    }
    printf("\n");
}

// ����������� ���������
int main() {
    PriorityQueue q;
    initQueue(&q);
    srand(time(0));

    // ��������� ��������� ��������� � ���������� ������������
    printf("Adding elements to the queue:\n");
    for (int i = 0; i < 10; i++) {
        int data = rand() % 100;
        int priority = rand() % (MAX_PRIORITY + 1);
        printf("Adding: %d (priority %d)\n", data, priority);
        enqueue(&q, data, priority);
    }
    printQueue(&q);

    // ���������� ��������� ���������� ���������
    printf("\nDequeue front: %d\n", dequeueFront(&q));
    printQueue(&q);

    int testPriority = rand() % (MAX_PRIORITY + 1);
    printf("\nDequeue with priority %d: %d\n", testPriority, dequeueWithPriority(&q, testPriority));
    printQueue(&q);

    int minTestPriority = rand() % (MAX_PRIORITY + 1);
    printf("\nDequeue with priority >= %d: %d\n", minTestPriority, dequeueWithMinPriority(&q, minTestPriority));
    printQueue(&q);

    return 0;
}