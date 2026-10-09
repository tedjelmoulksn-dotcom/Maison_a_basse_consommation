CXX ?= c++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Wpedantic -Werror -O2
SKETCH = arduino/Projet_Maison_Energetique

.PHONY: test sanitize clean
test: build/test_sensor build/test_sketch
	./build/test_sensor
	./build/test_sketch

build/test_sensor: tests/test_sensor.cpp $(SKETCH)/TCN75A.cpp $(SKETCH)/TCN75A.h $(SKETCH)/shutter_trigger.h tests/stubs/Arduino.h tests/stubs/Wire.h
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Itests/stubs -I$(SKETCH) tests/test_sensor.cpp $(SKETCH)/TCN75A.cpp -o $@

build/test_sketch: tests/test_sketch.cpp $(SKETCH)/Projet_Maison_Energetique.ino $(SKETCH)/TCN75A.cpp $(SKETCH)/TCN75A.h $(SKETCH)/shutter_trigger.h tests/stubs/Arduino.h tests/stubs/Wire.h tests/stubs/CheapStepper.h tests/stubs/LiquidCrystal_I2C.h
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Itests/stubs -I$(SKETCH) tests/test_sketch.cpp $(SKETCH)/TCN75A.cpp -o $@

sanitize:
	$(MAKE) clean
	$(MAKE) test CXXFLAGS="-std=c++11 -Wall -Wextra -Wpedantic -Werror -g -fsanitize=address,undefined -fno-omit-frame-pointer"

clean:
	rm -rf build
