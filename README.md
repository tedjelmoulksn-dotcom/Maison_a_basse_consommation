# Maison à Basse Consommation

An embedded systems project for an energy-efficient house model featuring Arduino-based thermal monitoring and environmental control.

> **Project Status**: Active development with modular hardware integration for temperature sensing, climate control, and automated systems.

---

## 📋 Table of Contents

- [About](#about)
- [Project Structure](#project-structure)
- [Hardware Components](#hardware-components)
- [Getting Started](#getting-started)
- [Key Features](#key-features)
- [Contributors](#contributors)
- [License](#license)

---

## About

**Maison à Basse Consommation** is an instrumentation project designed to simulate and monitor the thermal behavior of a low-energy residential building. The system integrates multiple sensors and actuators to model seasonal scenarios (winter/summer) and evaluate energy consumption through automated control of heating, cooling, and ventilation systems.

### Project Team
- Greg ALBERTS
- Sarah DAHMOUN
- Hugo LEBAUD
- Tedj El Moulk SINACER

---

## Project Structure

```
Maison_a_basse_consommation/
├── Maison energetique/
│   ├── Projet_Maison_Energetique.ino           # Main Arduino sketch
│   ├── Projet_Maison_Energetique(1).ino        # Alternative configuration
│   ├── Projet_Maison_Energetique(3).ino        # Advanced variant
│   ├── TCN75A.h                                # Temperature sensor header
│   ├── TCN75A.cpp                              # Temperature sensor implementation
│   ├── I2C_Scanning_Code.ino                   # I2C device discovery utility
│   ├── Test_temperature_sensor.ino             # Temperature sensor test
│   ├── moteur_pas_a_pas_test.ino               # Stepper motor test
│   ├── peltier.ino                             # Peltier module control
│   ├── peltier(1).ino                          # Alternative Peltier configuration
│   ├── stepper_turning.ino                     # Stepper motor control
│   ├── Test_Coffret_Conception...f3d           # CAD design files (Fusion 360)
│   ├── Enrouleur_MPAP v2.stl                   # 3D model for roller module
│   └── Schéma_électrique.pdn                   # Electrical schematic
└── README.md
```

---

## Hardware Components

The system integrates the following components:

| Component | Function | Control |
|-----------|----------|---------|
| **TCN75A** | I2C Temperature Sensor | Digital readout (±0.5°C resolution) |
| **Peltier Module** | Thermoelectric cooling/heating | PWM (Pin 3) |
| **Heating Resistor** | Thermal heating element | PWM (Pin 4) |
| **Solar Simulator** | Artificial solar radiation | PWM (Pin 5) |
| **Fan** | Air circulation/ventilation | PWM (Pin 6) |
| **Stepper Motor** | Automated blind/damper control | Digital control |
| **Status LEDs** | Winter/Summer mode indicators | Digital (Pins 9-10) |
| **Mode Buttons** | Season selection switches | Digital (Pins 7-8) |
| **LCD Display** | 20x4 I2C Display | I2C (Real-time monitoring) |
| **Potentiometer** | Manual control parameter | Analog (Pin 11) |

---

## Key Features

- **Temperature Monitoring**: Real-time thermal data acquisition via TCN75A I2C sensor
- **Multi-Stage Climate Control**: 
  - Peltier-based cooling
  - Resistive heating
  - Forced convection (fan)
- **Thermal Simulation**: Models winter and summer seasonal scenarios
- **Modular Architecture**: Separated component drivers and test utilities
- **LCD Dashboard**: Live temperature and system status display
- **PWM-based Control**: Precise power management for all actuators
- **Configurable Thresholds**: Adjustable temperature set-points and hysteresis

---

## Getting Started

### Prerequisites

- **Arduino IDE** (1.8.0 or later)
- **Arduino-compatible microcontroller** (Uno, Mega, etc.)
- **Required Libraries**:
  - `Wire.h` (I2C communication) — built-in
  - `LiquidCrystal_I2C.h` — install via Arduino IDE Library Manager
  - `TCN75A.h` — included in repository

### Installation

1. **Clone or download** this repository
2. **Open Arduino IDE** and navigate to:
   - File → Preferences → Additional Board Manager URLs
   - Add repository link if using custom board
3. **Install Dependencies**:
   - Sketch → Include Library → Manage Libraries
   - Search for and install `LiquidCrystal_I2C`
4. **Verify I2C Devices**:
   - Upload `I2C_Scanning_Code.ino` to identify connected devices
   - Open Serial Monitor (9600 baud) to view device addresses

### Upload Main Program

1. Open `Projet_Maison_Energetique.ino` in Arduino IDE
2. Select Tools → Board and Port (match your hardware)
3. Click Upload (→ arrow button)

### Test Individual Components

Before running the full system, test components individually:

```bash
# Temperature sensor
→ Upload: Test_temperature_sensor.ino

# Stepper motor
→ Upload: moteur_pas_a_pas_test.ino

# Peltier module
→ Upload: peltier.ino

# PWM devices
→ Uncomment test functions in main sketch
```

---

## Usage

### Main Sketch Operation

The `Projet_Maison_Energetique.ino` sketch provides:

**Uncomment functions in `loop()` to enable:**
- `fonctionTest_TemperatureSensor()` — Read temperature every 500ms
- `fonctionTest_Peltier(255)` — Activate cooling at full power
- `fonctionTest_ResistanceChauffante(255)` — Activate heating at full power
- `fonctionTest_Soleil(255)` — Activate solar simulator
- `fonctionTest_Ventilateur(255)` — Activate fan
- `fonctionTest_Lcd()` — Display test patterns on LCD
- `fonctionTest_Led()` — Blink status LEDs
- `fonctionTest_Bouton()` — Monitor button states
- `fonctionTest_Potentiometre()` — Read potentiometer position

### PWM Control

Control system power via PWM values (0–255):

```cpp
fonctionProjet_PWM("PELTIER", 200);      // 78% cooling power
fonctionProjet_PWM("RESISTANCE", 150);   // 59% heating power
fonctionProjet_PWM("SOLEIL", 255);       // Full solar simulation
fonctionProjet_PWM("VENTILATEUR", 100);  // 39% fan speed
```

### Temperature Monitoring

```cpp
float t = tcn.readTemperature();  // Read current temperature
tcn.setRangeTemp(18.0, 25.0);     // Set hysteresis (18°C) and limit (25°C)
```

### Serial Output

Sensor data and diagnostics are printed to Serial Monitor at **9600 baud**:

```
Temperature : 22.5
position_Potentiometre : 128
Bouton_Hiver : LOW
```

---

## Technical Notes

### I2C Addresses

- **TCN75A Sensor**: `0x48`
- **LCD Display**: `0x27`

### PWM Output Pins

- Pin 3: Peltier module
- Pin 4: Heating resistor
- Pin 5: Solar simulator
- Pin 6: Fan motor

### Temperature Sensor Specifications

- **Range**: -40°C to +125°C
- **Resolution**: 9-bit to 12-bit configurable
- **Accuracy**: ±0.5°C (typical)
- **Interface**: I2C (TWI)

---

## Contributing

Contributions and improvements are welcome. To contribute:

1. Test changes on physical hardware before submitting
2. Document any new functions or hardware additions
3. Provide both hardware schematics and code for complex features
4. Include test sketches for new components

---

## License

Specify LICENSE in repository root. If undefined, all rights reserved by default.

---

## Contact

**Repository**: [tedjelmoulksn-dotcom/Maison_a_basse_consommation](https://github.com/tedjelmoulksn-dotcom/Maison_a_basse_consommation)

**Questions or Issues**: Open an issue on GitHub

---

*Last Updated: July 2026 | Language: C++/Arduino*
