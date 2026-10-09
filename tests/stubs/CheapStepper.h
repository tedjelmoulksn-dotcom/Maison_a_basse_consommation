#ifndef TEST_STEPPER_H
#define TEST_STEPPER_H
class CheapStepper {
public:
    int position = 0;
    unsigned long steps = 0;
    CheapStepper(int = 8, int = 9, int = 10, int = 11) {}
    int getStep() { return position; }
    void step(bool clockwise) { position += clockwise ? 1 : -1; ++steps; }
    void moveTo(bool, int target) { position = target; }
};
#endif
