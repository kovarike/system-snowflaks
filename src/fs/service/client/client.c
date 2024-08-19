#include <thrift/transport/TTransport.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransport.h>
#include <thrift/client/TSyncClient.h>
#include <iostream>
#include "Snowflake.h" // Inclua o cabeçalho gerado pelo Thrift

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::client;
using namespace com::twitter::service::snowflake::gen;

int main() {
    // Conectar ao servidor Thrift
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    SnowflakeClient client(protocol);

    try {
        transport->open();

        // Chamada ao método do serviço
        std::string key = "example_key";
        int64_t uniqueId = client.getUniqueId(key);

        std::cout << "Unique ID: " << uniqueId << std::endl;

        transport->close();
    } catch (TException& tx) {
        std::cerr << "ERROR: " << tx.what() << std::endl;
    }

    return 0;
}
