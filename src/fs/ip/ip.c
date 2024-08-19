#include <stdlib.h>  // Adicione esta linha
#include <stdint.h>
#include "ip.h"

uint32_t generate_ip(uint8_t region, uint8_t subnet) {
    return (uint32_t)(region << 24) | (subnet << 16) | (rand() % 65536);
}
