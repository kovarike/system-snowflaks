#include <iostream>
#include <memory>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TFramedTransport.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/Thrift.h>
#include "Snowflake.h" // Inclua o cabeçalho gerado pelo Thrift

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::client;

template<typename T>
class ThriftClient {
public:
    ThriftClient(const std::string& hostname, int port, int timeout) {
        // Cria um socket e transporte
        socket_ = std::make_shared<TSocket>(hostname, port, timeout);
        transport_ = std::make_shared<TFramedTransport>(socket_);
        protocol_ = std::make_shared<TBinaryProtocol>(transport_);
    }

    void open() {
        try {
            transport_->open();
            std::cout << "Conectado a " << socket_->getSocket()->getRemoteSocketAddress() << std::endl;
        } catch (TTransportException& tx) {
            std::cerr << "Erro ao abrir transporte: " << tx.what() << std::endl;
            throw;
        }
    }

    std::shared_ptr<T> createClient() {
        return std::make_shared<T>(protocol_);
    }

    void close() {
        if (transport_->isOpen()) {
            transport_->close();
            std::cout << "Transporte fechado." << std::endl;
        }
    }

private:
    std::shared_ptr<TSocket> socket_;
    std::shared_ptr<TTransport> transport_;
    std::shared_ptr<TProtocol> protocol_;
};

int main() {
    const std::string hostname = "localhost"; // Altere conforme necessário
    const int port = 9090; // Altere conforme necessário
    const int timeout = 5000; // Timeout em milissegundos

    try {
        ThriftClient<SnowflakeClient> client(hostname, port, timeout);
        client.open();
        auto snowflakeClient = client.createClient();

        // Exemplo de chamada a um método no cliente Snowflake
        std::string key = "example_key";
        int64_t uniqueId = snowflakeClient->getUniqueId(key);
        std::cout << "Unique ID: " << uniqueId << std::endl;

        client.close();
    } catch (const std::exception& e) {
        std::cerr << "Ocorreu um erro: " << e.what() << std::endl;
    }

    return 0;
}
