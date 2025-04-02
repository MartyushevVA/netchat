#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Ошибка создания сокета\n";
        return -1;
    }

    // Настройка параметров сервера
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Привязка сокета к порту
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Ошибка привязки\n";
        return -1;
    }

    // Ожидание входящих соединений
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Ошибка ожидания соединений\n";
        return -1;
    }

    std::cout << "Ожидание подключения...\n";

    // Принятие входящего соединения
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Ошибка принятия соединения\n";
        return -1;
    }

    // Чтение данных от клиента
    read(new_socket, buffer, 1024);
    std::cout << "Клиент: " << buffer << "\n";

    // Отправка ответа клиенту
    const char* response = "Привет от сервера!";
    send(new_socket, response, strlen(response), 0);
    
    // Закрытие соединения
    close(new_socket);
    close(server_fd);

    return 0;
}
