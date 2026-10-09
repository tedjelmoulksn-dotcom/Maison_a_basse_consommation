#ifndef TEST_LCD_H
#define TEST_LCD_H
#include <cassert>
class LiquidCrystal_I2C {
    int columns, rows;
public:
    LiquidCrystal_I2C(int, int width, int height) : columns(width), rows(height) {}
    void init() {}
    void clear() {}
    void backlight() {}
    void setCursor(int col, int row) { assert(col >= 0 && col < columns && row >= 0 && row < rows); }
    template<class T> void print(const T &) {}
};
#endif
