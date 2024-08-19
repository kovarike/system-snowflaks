#include <stdio.h>
#include <stdint.h>
#include "fs/uuid/uuid.h"
#include "fs/ip/ip.h"
#include "fs/crypto/crypto.h"

int main() {
    uint64_t uuid = generate_uuid(1, 1);
    uint32_t ip = generate_ip(1, 1);

    uint8_t data[16] = "hello world!";
    uint8_t key[16] = "mysecretkey1234";
    
    aes_encrypt(data, 16, key);
    printf("Encrypted data: %s\n", data);

    aes_decrypt(data, 16, key);
    printf("Decrypted data: %s\n", data);

    printf("Generated UUID: %lu\n", uuid);
    printf("Generated IP: %u.%u.%u.%u\n", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

    return 0;
}
