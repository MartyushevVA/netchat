#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main() {
    try {
        boost::asio::io_context io_context;

        // Получаем endpoint сервера (IP и порт)
        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint = *resolver.resolve(udp::v4(), "127.0.0.1", "9000").begin();

        // Создаём и открываем сокет
        udp::socket socket(io_context);
        socket.open(udp::v4());

        // Сообщение для отправки
        std::string message = "Привет от UDP-клиента!";

        // Отправляем сообщение серверу
        socket.send_to(boost::asio::buffer(message), receiver_endpoint);

        // Подготавливаем буфер для ответа от сервера
        char reply[1024];
        udp::endpoint sender_endpoint;
        boost::system::error_code error;

        // Получаем ответ
        size_t reply_length = socket.receive_from(
            boost::asio::buffer(reply), sender_endpoint, 0, error
        );

        if (!error) {
            std::cout << "Ответ от сервера: " << std::string(reply, reply_length) << "\n";
        } else {
            std::cerr << "Ошибка получения ответа: " << error.message() << "\n";
        }

    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
