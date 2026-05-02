#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

// Функция для проверки принадлежности IP адреса к подсети
int is_in_subnet(uint32_t ip, uint32_t gateway, uint32_t mask) {
    return (ip & mask) == (gateway & mask);
}

// Функция для преобразования строки IP в uint32_t с помощью побитовых операций
int ip_to_uint32(const char* ip_str, uint32_t* ip_uint) {
    unsigned int bytes[4];
    if (sscanf(ip_str, "%u.%u.%u.%u", &bytes[0], &bytes[1], &bytes[2], &bytes[3]) != 4) {
        return 0;
    }
    
    // Проверка валидности каждого байта
    for (int i = 0; i < 4; i++) {
        if (bytes[i] > 255) {
            return 0;
        }
    }
    
    // Сборка uint32_t из байтов в сетевом порядке 
    *ip_uint = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    return 1;
}

// Исправленная функция для генерации случайного IP адреса
uint32_t generate_random_ip() {
    // Генерируем все 32 бита случайно
    uint8_t byte1 = rand() % 256;
    uint8_t byte2 = rand() % 256;
    uint8_t byte3 = rand() % 256;
    uint8_t byte4 = rand() % 256;
    
    return ((uint32_t)byte1 << 24) | ((uint32_t)byte2 << 16) | 
           ((uint32_t)byte3 << 8) | (uint32_t)byte4;
}

// Функция для преобразования uint32_t в строку IP с помощью побитовых операций
void uint32_to_ip(uint32_t ip_uint, char* ip_str) {
    uint8_t byte1 = (ip_uint >> 24) & 0xFF;
    uint8_t byte2 = (ip_uint >> 16) & 0xFF;
    uint8_t byte3 = (ip_uint >> 8) & 0xFF;
    uint8_t byte4 = ip_uint & 0xFF;
    
    sprintf(ip_str, "%u.%u.%u.%u", byte1, byte2, byte3, byte4);
}

// Отладочная функция для вывода IP в разных форматах
void debug_ip_info(const char* label, uint32_t ip) {
    char ip_str[16];
    uint32_to_ip(ip, ip_str);
    printf("%s: %s (0x%08X, %u)\n", label, ip_str, ip, ip);
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
    
    // Вывод отладочной информации
    printf("--- Отладочная информация ---\n");
    debug_ip_info("Шлюз", gateway);
    debug_ip_info("Маска", mask);
    
    uint32_t network = gateway & mask;
    printf("Подсеть: ");
    debug_ip_info("", network);
    
    // Проверка, что функция is_in_subnet работает корректно
    uint32_t test_ip1, test_ip2;
    ip_to_uint32("192.168.1.100", &test_ip1);
    ip_to_uint32("192.168.2.1", &test_ip2);
    
    printf("\nТест is_in_subnet:\n");
    printf("192.168.1.100 в сети 192.168.1.1/255.255.255.0: %s\n", 
           is_in_subnet(test_ip1, gateway, mask) ? "Да" : "Нет");
    printf("192.168.2.1 в сети 192.168.1.1/255.255.255.0: %s\n", 
           is_in_subnet(test_ip2, gateway, mask) ? "Да" : "Нет");
    
    srand(time(NULL));
    
    int same_subnet = 0;
    char ip_str[16];
    
    printf("\n--- Первые 10 сгенерированных IP ---\n");
    for (int i = 0; i < 10; i++) {
        uint32_t test_gen_ip = generate_random_ip();
        uint32_to_ip(test_gen_ip, ip_str);  
        printf("Сгенерирован IP: %s\n", ip_str);
    }
    
    printf("\nИмитация отправки %d пакетов...\n", n);
    
    for (int i = 0; i < n; i++) {
        uint32_t dest_ip = generate_random_ip();
        uint32_to_ip(dest_ip, ip_str);
        
        if (is_in_subnet(dest_ip, gateway, mask)) {
            same_subnet++;
            if (same_subnet <= 5) {  // Показываем только первые 5 своих пакетов
                printf("Пакет %d: %s - своя подсеть\n", i+1, ip_str);
            }
        }
    }
    
    // Вывод статистики
    printf("\n--- Статистика ---\n");
    printf("Пакетов в своей подсети: %d (%.2f%%)\n",
           same_subnet, (float)same_subnet / n * 100);
    printf("Пакетов в других сетях: %d (%.2f%%)\n",
           n - same_subnet, (float)(n - same_subnet) / n * 100);
    
    // Расчет ожидаемого процента
    uint32_t hosts_in_subnet = (~mask) + 1;  // Количество хостов в подсети
    double expected_percentage = (double)hosts_in_subnet / 4294967296.0 * 100.0;
    printf("Ожидаемый процент: %.4f%% (размер подсети: %u хостов)\n", 
           expected_percentage, hosts_in_subnet);
    
    return 0;
}