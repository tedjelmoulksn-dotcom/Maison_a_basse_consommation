#include <CheapStepper.h>

CheapStepper stepper(2, 3, 4, 5);  // Initialisation du moteur a modifer si necessaier 

int nombre_de_pas = 4096;         // Nombre de pas pour un tour complet a tester surtout 
int position_defaut = 0;          // Position initiale

void setup() {
  Serial.begin(9600);
  Serial.println("Initialisation du moteur pas à pas...");

  // Enregistrer la position par défaut
  position_defaut = stepper.getStep();
  Serial.print("Position par défaut : ");
  Serial.println(position_defaut);

  // DESCENTE : faire 4096 pas dans une direction
  Serial.println("Descente...");
  for (int i = 0; i < nombre_de_pas; i++) {
    stepper.step(false);  // false = sens antihoraire
  }

  delay(2000); // Pause

  // REMONTER : refaire le même nombre de pas dans l'autre sens
  Serial.println("Remontée...");
  for (int i = 0; i < nombre_de_pas; i++) {
    stepper.step(true);  // true = sens horaire
  }

  delay(2000);

  Serial.print("Position finale (devrait être la même que la position de départ) : ");
  Serial.println(stepper.getStep());
}

void loop() {
  // Ne rien faire dans loop
}
