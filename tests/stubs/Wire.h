#ifndef TEST_WIRE_H
#define TEST_WIRE_H
#include <stdint.h>
#include <stddef.h>
#include <vector>
class TwoWire {
public:
    std::vector<int> bytes;
    size_t position = 0;
    uint8_t status = 0, reported_count = 2, pointer = 0;
    void begin() {}
    void beginTransmission(uint8_t) {}
    void write(uint8_t value) { pointer = value; }
    uint8_t endTransmission(bool = true) { return status; }
    uint8_t requestFrom(uint8_t, uint8_t) { position = 0; return reported_count; }
    int available() { return static_cast<int>(bytes.size() - position); }
    int read() { return position < bytes.size() ? bytes[position++] : -1; }
};
extern TwoWire Wire;
#endif
