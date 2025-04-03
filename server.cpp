#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        // Создание TCP-акцептора (прослушивает входящие соединения)
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Ожидание клиента...\n";

        // Создание сокета для клиента
        tcp::socket socket(io_context);
        acceptor.accept(socket);  // Ожидание подключения

        std::cout << "Клиент подключен!\n";

        // Чтение данных от клиента
        char buffer[1024] = {0};
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(buffer), error);

        if (!error) {
            std::cout << "Клиент: " << std::string(buffer, length) << "\n";

            // Отправка ответа клиенту
            std::string response = "Привет от сервера!";
            boost::asio::write(socket, boost::asio::buffer(response), error);
        } else {
            std::cerr << "Ошибка чтения: " << error.message() << "\n";
        }
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
