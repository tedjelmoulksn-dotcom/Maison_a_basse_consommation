#include <cassert>
#include <cmath>
#include <cstdio>
#include "TCN75A.h"
#include "shutter_trigger.h"
TwoWire Wire;

static void sample(TCN75A &sensor, int high, int low, float expected)
{
    Wire.bytes = {high, low};
    assert(std::fabs(sensor.readTemperature() - expected) < 0.00001f);
    assert(Wire.pointer == 0x00);
}

int main()
{
    TCN75A sensor(0x48);
    assert(std::isnan(sensor.readTemperature()));
    sensor.begin();
    sample(sensor, 0x19, 0x10, 25.0625f);
    sample(sensor, 0xff, 0xf0, -0.0625f);
    sample(sensor, 0xf5, 0x80, -10.5f);
    sample(sensor, 0xd8, 0x00, -40.0f);
    sample(sensor, 0x7d, 0x00, 125.0f);
    sample(sensor, 0x00, 0x00, 0.0f);
    Wire.bytes = {0xff, 0x80};
    assert(sensor.getHystTemp() == -0.5f);
    assert(Wire.pointer == 0x02);
    Wire.bytes = {0x17, 0x80};
    assert(sensor.getLimitTemp() == 23.5f);
    assert(Wire.pointer == 0x03);
    Wire.status = 2;
    assert(std::isnan(sensor.readTemperature()));
    Wire.status = 0;
    Wire.reported_count = 1;
    assert(std::isnan(sensor.readTemperature()));
    Wire.reported_count = 2;
    Wire.bytes = {0x19};
    assert(std::isnan(sensor.readTemperature()));
    Wire.bytes = {-1, 0};
    assert(std::isnan(sensor.readTemperature()));
    int state = 1;
    assert(!shutterCycleRequested(32, state));
    assert(shutterCycleRequested(33, state));
    assert(!shutterCycleRequested(33, state));
    assert(!shutterCycleRequested(31, state));
    assert(!shutterCycleRequested(NAN, state));
    assert(!shutterCycleRequested(30, state));
    assert(shutterCycleRequested(33, state));
    std::puts("TCN75A signed decoding, I2C errors and shutter hysteresis: PASS");
}
