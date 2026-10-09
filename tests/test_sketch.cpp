#include "Arduino.h"
#include "Wire.h"
#include <cassert>
#include <cstdio>

int mock_pwm[64] = {};
int mock_digital[64] = {};
MockSerial Serial;
TwoWire Wire;

// Arduino's build normally generates these forward declarations.
void fonctionProjet_PWM(const char *, int);
void fonctionProjet_TemperatureSensor();
void fonctionProjet_MoteurPasAPas();
void fonctionTest_TemperatureSensor();
void fonctionTest_MoteurPasAPas();
void fonctionTest_Peltier(int);
void fonctionTest_ResistanceChauffante(int);
void fonctionTest_Soleil(int);
void fonctionTest_Ventilateur(int);
void fonctionTest_Lcd();
void fonctionTest_Led();
void fonctionTest_Bouton();
void fonctionTest_Potentiometre();
#include "../arduino/Projet_Maison_Energetique/Projet_Maison_Energetique.ino"

int main()
{
    setup();
    char identifier[] = "PELTIER";
    fonctionProjet_PWM(identifier, 100);
    assert(mock_pwm[pin_Peltier] == 100);
    fonctionProjet_PWM(identifier, 999);
    assert(mock_pwm[pin_Peltier] == 255);
    fonctionProjet_PWM(identifier, -1);
    assert(mock_pwm[pin_Peltier] == 0);
    fonctionProjet_PWM(NULL, 123);
    fonctionTest_Lcd(); // All cursor positions must fit the 20x4 display.
    mock_digital[pin_Bouton_Ete] = LOW;
    mock_digital[pin_Bouton_Hiver] = HIGH;
    Wire.status = 2;
    loop();
    assert(mock_pwm[pin_Resistance_Chauffante] == 0);
    assert(mock_pwm[pin_Soleil] == 0);
    assert(mock_pwm[pin_Peltier] == 0);
    assert(stepper.steps == 0);
    Wire.status = 0;
    Wire.bytes = {33, 0};
    loop();
    unsigned long cycle_steps = 2UL * nombre_de_pas;
    assert(stepper.steps == cycle_steps);
    assert(compteur == 2);
    loop();
    assert(stepper.steps == cycle_steps);
    Wire.bytes = {30, 0};
    loop();
    assert(compteur == 1);
    Wire.bytes = {33, 0};
    loop();
    assert(stepper.steps == 2 * cycle_steps);
    assert(stepper.getStep() == position_defaut);
    std::puts("Integration sketch PWM dispatch, sensor fault and shutter rearm: PASS");
}
