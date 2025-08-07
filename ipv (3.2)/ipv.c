#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

// Функция для проверки принадлежности IP адреса к подсети
int is_in_subnet(uint32_t ip, uint32_t gateway, uint32_t mask) {
    return (ip & mask) == (gateway & mask);
}

// Функция для преобразования строки IP в uint32_t
int ip_to_uint32(const char* ip_str, uint32_t* ip_uint) {
    struct in_addr addr;
    if (inet_pton(AF_INET, ip_str, &addr) != 1) {
        return 0;
    }
    *ip_uint = ntohl(addr.s_addr);
    return 1;
}

// Функция для генерации случайного IP адреса
uint32_t generate_random_ip() {
    return (uint32_t)rand() << 16 | rand();
}

// Функция для преобразования uint32_t в строку IP
void uint32_to_ip(uint32_t ip_uint, char* ip_str) {
    struct in_addr addr;
    addr.s_addr = htonl(ip_uint);
    inet_ntop(AF_INET, &addr, ip_str, INET_ADDRSTRLEN);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Использование: %s <шлюз> <маска> <количество пакетов>\n", argv[0]);
        return 1;
    }

    uint32_t gateway, mask;
    if (!ip_to_uint32(argv[1], &gateway) || !ip_to_uint32(argv[2], &mask)) {
        printf("Ошибка: неверный формат IP адреса или маски\n");
        return 1;
    }

    int n = atoi(argv[3]);
    if (n <= 0) {
        printf("Ошибка: количество пакетов должно быть положительным числом\n");
        return 1;
    }

    srand(time(NULL)); // Инициализация генератора случайных чисел

    int same_subnet = 0;
    char ip_str[INET_ADDRSTRLEN];

    printf("Имитация отправки %d пакетов...\n", n);
    for (int i = 0; i < n; i++) {
        uint32_t dest_ip = generate_random_ip();
        uint32_to_ip(dest_ip, ip_str);

        if (is_in_subnet(dest_ip, gateway, mask)) {
            same_subnet++;
            printf("Пакет %d: %s - своя подсеть\n", i+1, ip_str);
        } else {
            printf("Пакет %d: %s - чужая подсеть\n", i+1, ip_str);
        }
    }

    // Вывод статистики
    printf("\nСтатистика:\n");
    printf("Пакетов в своей подсети: %d (%.2f%%)\n", 
           same_subnet, (float)same_subnet / n * 100);
    printf("Пакетов в других сетях: %d (%.2f%%)\n", 
           n - same_subnet, (float)(n - same_subnet) / n * 100);

    return 0;
}