#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Ошибка создания сокета\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование IP-адреса
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Неверный адрес\n";
        return -1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Ошибка подключения\n";
        return -1;
    }

    // Отправка сообщения серверу
    const char* message = "Привет, сервер!";
    send(sock, message, strlen(message), 0);

    // Получение ответа от сервера
    read(sock, buffer, 1024);
    std::cout << "Сервер: " << buffer << "\n";

    // Закрытие сокета
    close(sock);

    return 0;
}
