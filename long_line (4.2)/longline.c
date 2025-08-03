#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRIORITY 255

// Структура элемента очереди
typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

// Структура очереди с приоритетом
typedef struct {
    Node* front;
} PriorityQueue;

// Инициализация очереди
void initQueue(PriorityQueue* q) {
    q->front = NULL;
}

// Добавление элемента в очередь с приоритетом
void enqueue(PriorityQueue* q, int data, int priority) {
    if (priority < 0 || priority > MAX_PRIORITY) {
        printf("Invalid priority! Must be between 0 and %d\n", MAX_PRIORITY);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    // Если очередь пуста или новый элемент имеет более высокий приоритет, чем первый
    if (q->front == NULL || priority > q->front->priority) {
        newNode->next = q->front;
        q->front = newNode;
    } else {
        Node* current = q->front;
        // Находим место для вставки
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Извлечение первого элемента из очереди
int dequeueFront(PriorityQueue* q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1; // или другое значение, обозначающее ошибку
    }

    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    free(temp);
    return data;
}

// Извлечение элемента с указанным приоритетом
int dequeueWithPriority(PriorityQueue* q, int priority) {
    if (priority < 0 || priority > MAX_PRIORITY) {
        printf("Invalid priority! Must be between 0 and %d\n", MAX_PRIORITY);
        return -1;
    }

    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    // Если первый элемент имеет нужный приоритет
    if (q->front->priority == priority) {
        return dequeueFront(q);
    }

    Node* current = q->front;
    Node* prev = NULL;

    // Ищем элемент с нужным приоритетом
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

// Извлечение элемента с приоритетом не ниже заданного
int dequeueWithMinPriority(PriorityQueue* q, int minPriority) {
    if (minPriority < 0 || minPriority > MAX_PRIORITY) {
        printf("Invalid priority! Must be between 0 and %d\n", MAX_PRIORITY);
        return -1;
    }

    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    // Если первый элемент удовлетворяет условию
    if (q->front->priority >= minPriority) {
        return dequeueFront(q);
    }

    Node* current = q->front;
    Node* prev = NULL;

    // Ищем первый элемент с подходящим приоритетом
    while (current != NULL && current->priority < minPriority) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("No element with priority >= %d found!\n", minPriority);
        return -1;
    }

    // Если это первый элемент в очереди
    if (prev == NULL) {
        q->front = current->next;
    } else {
        prev->next = current->next;
    }

    int data = current->data;
    free(current);
    return data;
}

// Печать очереди (для отладки)
void printQueue(PriorityQueue* q) {
    Node* current = q->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("[%d (prio %d)] ", current->data, current->priority);
        current = current->next;
    }
    printf("\n");
}

// Тестирующая программа
int main() {
    PriorityQueue q;
    initQueue(&q);
    srand(time(0));

    // Генерация случайных сообщений с различными приоритетами
    printf("Adding elements to the queue:\n");
    for (int i = 0; i < 10; i++) {
        int data = rand() % 100;
        int priority = rand() % (MAX_PRIORITY + 1);
        printf("Adding: %d (priority %d)\n", data, priority);
        enqueue(&q, data, priority);
    }
    printQueue(&q);

    // Извлечение элементов различными способами
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