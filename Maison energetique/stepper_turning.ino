#include <CheapStepper.h>
CheapStepper stepper;
boolean moveClockwise = true;  // direction de rotation
int position_defaut = 0;        // Position par défaut

void setup() {
  Serial.begin(9600);
  Serial.println("28BYJ-48 prêt.");
  
  // Déplacer le moteur à la position par défaut
  stepper.moveTo(true, 960);  // Se déplace vers le pas 960
  position_defaut = stepper.getStep();  // Enregistrer la position par défaut
  Serial.print("Position par défaut définie à : ");
  Serial.println(position_defaut);

  // Tour complet dans une direction
  for (int s = 0; s < 4096; s++) {
    stepper.step(moveClockwise);
    int nStep = stepper.getStep();

    if (nStep % 64 == 0) {  // Afficher toutes les 64 étapes
      Serial.print("Position actuelle : ");
      Serial.println(nStep);
    }
  }

  delay(1000);  // Attendre 1 seconde après le tour complet

  // Revenir à la position par défaut
  Serial.println("Retour à la position par défaut...");
  stepper.moveTo(true, position_defaut);
  
  Serial.print("Position actuelle après retour : ");
  Serial.println(stepper.getStep());
  
  delay(1000);  // Attendre 1 seconde
}

void loop() {
  // Laisser vide pour ne pas répéter le mouvement
}
