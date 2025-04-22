#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main() {
    try {
        boost::asio::io_context io_context;

        // Создаём UDP-сокет и привязываем его к порту 9000 (на всех доступных интерфейсах)
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 9000));

        std::cout << "UDP-сервер запущен на порту 9000\n";

        while (true) {
            char data[1024]; // Буфер для входящих данных
            udp::endpoint sender_endpoint; // Хранит адрес отправителя
            boost::system::error_code error;

            // Ожидаем получение данных от клиента
            size_t length = socket.receive_from(
                boost::asio::buffer(data), sender_endpoint, 0, error
            );

            // Проверка ошибок
            if (error && error != boost::asio::error::message_size)
                throw boost::system::system_error(error);

            // Преобразуем полученные байты в строку
            std::string message(data, length);
            std::cout << "Получено от " << sender_endpoint << ": " << message << "\n";

            // Отправляем простой ответ клиенту
            std::string response = "Принято: " + message;
            socket.send_to(boost::asio::buffer(response), sender_endpoint);
        }

    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
