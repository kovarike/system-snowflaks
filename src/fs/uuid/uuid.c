#include "uuid.h"
#include <time.h>

#define EPOCH 1609459200000LL // January 1, 2021

static uint64_t last_timestamp = 0;
static uint64_t sequence = 0;

uint64_t current_timestamp() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

uint64_t generate_uuid(uint64_t node_id, uint64_t datacenter_id) {
    uint64_t timestamp = current_timestamp();

    if (timestamp == last_timestamp) {
        sequence = (sequence + 1) & 0xFFF; // 4095
        if (sequence == 0) {
            while (timestamp <= last_timestamp) {
                timestamp = current_timestamp();
            }
        }
    } else {
        sequence = 0;
    }

    last_timestamp = timestamp;

    return ((timestamp - EPOCH) << 22) | (datacenter_id << 17) | (node_id << 12) | sequence;
}
