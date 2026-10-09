#ifndef SHUTTER_TRIGGER_H
#define SHUTTER_TRIGGER_H
#include <math.h>

/* Retain the existing 32 C test threshold. Rearm at 30 C to avoid
 * repeating the down/up demonstration while the temperature remains high.
 * This is a test-cycle trigger, not a seasonal temperature regulator.
 */
static bool shutterCycleRequested(float temperature, int &state)
{
    if (!isfinite(temperature)) return false;
    if (temperature <= 30.0f) state = 1;
    if (state == 1 && temperature > 32.0f) {
        state = 2;
        return true;
    }
    return false;
}
#endif
