#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

// Определяем структуры и типы здесь (дублируем минимально необходимое)
#define MAX_LENGTH 100

typedef struct ContactNode {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char workplace[MAX_LENGTH];
    char position[MAX_LENGTH];
    char phone[MAX_LENGTH];
    char email[MAX_LENGTH];
    char social[MAX_LENGTH];
    char messenger[MAX_LENGTH];

    struct ContactNode* prev;
    struct ContactNode* next;
} ContactNode;

typedef struct {
    ContactNode* head;
    ContactNode* tail;
    int count;
} ContactList;

// Типы указателей на функции из динамической библиотеки
typedef void (*initList_func)(ContactList*);
typedef void (*freeList_func)(ContactList*);
typedef void (*addContact_func)(ContactList*);
typedef void (*displayContacts_func)(ContactList*);
typedef void (*editContact_func)(ContactList*);
typedef void (*deleteContact_func)(ContactList*);

int main() {
    void* handle = NULL;
    ContactList phoneBook;

    // === Динамическая загрузка библиотеки ===
    handle = dlopen("./libs_so/libph.so", RTLD_LAZY | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    // Загружаем все необходимые функции
    initList_func     initList      = (initList_func)     dlsym(handle, "initList");
    freeList_func     freeList      = (freeList_func)     dlsym(handle, "freeList");
    addContact_func   addContact    = (addContact_func)   dlsym(handle, "addContact");
    displayContacts_func displayContacts = (displayContacts_func) dlsym(handle, "displayContacts");
    editContact_func  editContact   = (editContact_func)  dlsym(handle, "editContact");
    deleteContact_func deleteContact = (deleteContact_func) dlsym(handle, "deleteContact");

    // Проверка ошибок
    const char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка получения символов из библиотеки: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Инициализация списка
    initList(&phoneBook);
    printf("Динамическая библиотека libph.so успешно загружена!\n");
    printf("=== Телефонная книга (двухсвязный упорядоченный список) ===\n\n");

    int choice;
    do {
        printf("1. Добавить контакт\n");
        printf("2. Просмотреть все контакты\n");
        printf("3. Редактировать контакт\n");
        printf("4. Удалить контакт\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        getchar(); // очистка буфера ввода

        switch (choice) {
            case 1:
                addContact(&phoneBook);
                break;
            case 2:
                displayContacts(&phoneBook);
                break;
            case 3:
                editContact(&phoneBook);
                break;
            case 4:
                deleteContact(&phoneBook);
                break;
            case 0:
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 0);

    // Освобождение ресурсов
    freeList(&phoneBook);
    dlclose(handle);

    printf("Программа завершена.\n");
    return 0;
}