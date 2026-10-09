#ifndef TEST_ARDUINO_H
#define TEST_ARDUINO_H
#include <stdint.h>
#include <math.h>
#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define INPUT_PULLUP 2
extern int mock_pwm[64];
extern int mock_digital[64];
inline void pinMode(int, int) {}
inline void analogWrite(int pin, int value) { mock_pwm[pin] = value; }
inline void digitalWrite(int pin, int value) { mock_digital[pin] = value; }
inline int digitalRead(int pin) { return mock_digital[pin]; }
inline int analogRead(int) { return 0; }
inline void delay(unsigned long) {}
template<class T> T constrain(T x, T low, T high) { return x < low ? low : (x > high ? high : x); }
class MockSerial {
public:
    void begin(long) {}
    template<class T> void print(const T &) {}
    template<class T> void println(const T &) {}
};
extern MockSerial Serial;
#define bitWrite(value, bit, on) ((on) ? ((value) |= (1U << (bit))) : ((value) &= ~(1U << (bit))))
#define bitRead(value, bit) (((value) >> (bit)) & 1U)
#endif
