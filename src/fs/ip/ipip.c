#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <ifaddrs.h>
#endif

void get_ip_address() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Erro ao inicializar Winsock.\n");
        return;
    }

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    struct hostent *host_info = gethostbyname(hostname);
    if (host_info == NULL) {
        printf("Erro ao obter o endereço IP.\n");
        WSACleanup();
        return;
    }

    for (int i = 0; host_info->h_addr_list[i] != NULL; i++) {
        struct in_addr addr;
        memcpy(&addr, host_info->h_addr_list[i], sizeof(struct in_addr));
        printf("Endereço IP: %s\n", inet_ntoa(addr));
    }

    WSACleanup();
#else
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        if (ifa->ifa_addr->sa_family == AF_INET) { // IPv4
            char ip[INET_ADDRSTRLEN];
            getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
                        ip, sizeof(ip), NULL, 0, NI_NUMERICHOST);
            printf("Interface: %s \t Endereço IP: %s\n", ifa->ifa_name, ip);
        }
    }

    freeifaddrs(ifaddr);
#endif
}

int main() {
    printf("Buscando o endereço IP...\n");
    get_ip_address();
    return 0;
}
