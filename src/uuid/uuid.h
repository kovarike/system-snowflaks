#ifndef UUID_H
#define UUID_H

#include <stdint.h>

uint64_t generate_uuid(uint64_t node_id, uint64_t datacenter_id);

#endif
