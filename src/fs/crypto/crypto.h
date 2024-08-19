#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>
#include <stddef.h>

void aes_encrypt(uint8_t* data, size_t length, const uint8_t* key);
void aes_decrypt(uint8_t* data, size_t length, const uint8_t* key);

void rsa_encrypt(uint8_t* data, size_t length, const uint8_t* public_key);
void rsa_decrypt(uint8_t* data, size_t length, const uint8_t* private_key);

#endif
