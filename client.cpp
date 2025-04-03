#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        // Создание сокета
        tcp::socket socket(io_context);

        // Подключение к серверу
        socket.connect(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 8080));

        std::cout << "Подключено к серверу!\n";

        // Отправка сообщения серверу
        std::string message = "Привет, сервер!";
        boost::asio::write(socket, boost::asio::buffer(message));

        // Получение ответа от сервера
        char buffer[1024] = {0};
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(buffer), error);

        if (!error) {
            std::cout << "Сервер: " << std::string(buffer, length) << "\n";
        } else {
            std::cerr << "Ошибка чтения: " << error.message() << "\n";
        }

    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
