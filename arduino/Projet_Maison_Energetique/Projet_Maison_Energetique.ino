/* -------------------------------------------------------------------------------------------
| PROJET INSTRUMENTATION : Greg ALBERTS, Sarah DAHMOUN, Hugo LEBAUD, Tedj El Moulk SINACER   |
------------------------------------------------------------------------------------------- */

#include <Wire.h>   // library used with I2C protocol
#include "TCN75A.h"
#include "shutter_trigger.h"
#include <math.h>
#include <string.h>
#include <LiquidCrystal_I2C.h> // Nécessite l'installation de la bibliothèque LiquidCrystal_I2C 
#include <CheapStepper.h> //Librairie pour le module du moteur pas a pas 
                               //dans le gestionnaire de bibliothèque intégré à Arduino IDE

int nombre_de_pas = 4096*2;         // Nombre de pas pour un tour complet a tester surtout 
int position_defaut = 0;          // Position initiale

int pin_Peltier = 12; 
int pin_Resistance_Chauffante = 11;
int pin_Soleil = 10;
int pin_sig_ServoMoteurSoleil = 4;
int pin_Ventilateur = 13;
int pin_Bouton_Hiver = 2;
int pin_Bouton_Ete = 3;
int pin_Led_Hiver = 50;
int pin_Led_Ete = 37;
int pin_Potentiometre = 0;
CheapStepper stepper(32,28,30,22);// a choisir les pin convenable sinn c (8,9,10,11) par defaut;
TCN75A tcn(0x48);
LiquidCrystal_I2C lcd(0x27, 20, 4);
int compteur = 1; // Armed; rearm after cooling below the trigger hysteresis.

void setup() {
  Serial.begin(9600);  // Initialise le port série
  Wire.begin();  // Initialise l'I2C avec les broches définies
  tcn.begin();  // Initialise le capteur
  lcd.init();// Initialise le LCD
  
  // Initialisation des pins
  pinMode(pin_Peltier, OUTPUT);
  pinMode(pin_Resistance_Chauffante, OUTPUT);
  pinMode(pin_Soleil, OUTPUT);
  pinMode(pin_Ventilateur, OUTPUT);
  pinMode(pin_Bouton_Hiver, INPUT_PULLUP);
  pinMode(pin_Bouton_Ete, INPUT_PULLUP);
  pinMode(pin_Led_Hiver, OUTPUT);
  pinMode(pin_Led_Ete, OUTPUT);

  // Enregistrer la position par défaut
  position_defaut = stepper.getStep();
  Serial.print("Position par défaut : ");
  Serial.println(position_defaut);
}

void loop() {  
  // Mode Ete
  if(digitalRead(pin_Bouton_Ete) == LOW)
  {
    // fonctionTest_TemperatureSensor();
    // fonctionTest_MoteurPasAPas();
    // fonctionTest_Peltier(100);
    fonctionTest_ResistanceChauffante(100);
    fonctionTest_Soleil(50);
    fonctionTest_Ventilateur(255);
    // fonctionTest_Lcd();
    // fonctionTest_Led();
    // fonctionTest_Bouton();
    // fonctionTest_Potentiometre();

    digitalWrite(pin_Led_Ete, HIGH);
    digitalWrite(pin_Led_Hiver, LOW);

    // fonctionTest_Lcd();
  }
  // Mode Hiver
  else if(digitalRead(pin_Bouton_Hiver) == LOW)
  {
    // fonctionTest_TemperatureSensor();
    // fonctionTest_MoteurPasAPas();
    // fonctionTest_Peltier(100);
    fonctionTest_ResistanceChauffante(0);
    fonctionTest_Soleil(0);
    fonctionTest_Ventilateur(255);
    // fonctionTest_Lcd();
    // fonctionTest_Led();
    // fonctionTest_Bouton();
    // fonctionTest_Potentiometre();

    digitalWrite(pin_Led_Hiver, HIGH);
    digitalWrite(pin_Led_Ete, LOW);

    // fonctionTest_Lcd();
  }

  fonctionProjet_TemperatureSensor();
}

/* ----- Début : FONCTIONS DU PROJET ----- */

// Fonction permettant selon le composant, de lui envoyer une commande PWM
void fonctionProjet_PWM(const char* nom_composant, int valeur_PWM)
{
  if (!nom_composant) return;
  valeur_PWM = constrain(valeur_PWM, 0, 255);
  if(strcmp(nom_composant, "PELTIER") == 0)
  {
    analogWrite(pin_Peltier, valeur_PWM);
  }
  else if(strcmp(nom_composant, "RESISTANCE") == 0)
  {
    analogWrite(pin_Resistance_Chauffante, valeur_PWM);
  }
  else if(strcmp(nom_composant, "SOLEIL") == 0)
  {
    analogWrite(pin_Soleil, valeur_PWM);
  }
  else if(strcmp(nom_composant, "VENTILATEUR") == 0)
  {
    analogWrite(pin_Ventilateur, valeur_PWM);
  }
}

// Fonction permettant de lire la température intérieure grâce au capteur
void fonctionProjet_TemperatureSensor()
{
  float t = tcn.readTemperature();
  
  if (!isfinite(t)) {
    // Stop thermal loads on an invalid reading; keep ventilation available.
    analogWrite(pin_Peltier, 0);
    analogWrite(pin_Resistance_Chauffante, 0);
    analogWrite(pin_Soleil, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor read error");
    Serial.println("Sensor read error: thermal loads disabled.");
    delay(500);
    return;
  }
  if (shutterCycleRequested(t, compteur)) {
    fonctionProjet_MoteurPasAPas();
  }

  lcd.backlight();
  // Envoi du message sur le LCD : ----->>>> (colonne, ligne)
  lcd.setCursor(1,0);
  lcd.print("Temperature : ");
  lcd.setCursor(15, 0);
  lcd.print(t);
  lcd.setCursor(5, 1);
  lcd.print("compteur = ");
  lcd.setCursor(15, 1);
  lcd.print(compteur);
  delay(500);
  lcd.clear();

  Serial.println("Temperature : ");
  Serial.println(t);
  delay(500);
}

void fonctionProjet_MoteurPasAPas()
{
  // DESCENTE : faire 4096 pas dans une direction
  Serial.println("Descente...");
  for (int i = 0; i < nombre_de_pas; i++) {
    stepper.step(true);  // false = sens antihoraire
  }

  delay(2000); // Pause

  // REMONTER : refaire le même nombre de pas dans l'autre sens
  Serial.println("Remontée...");
  for (int i = 0; i < nombre_de_pas; i++) {
    stepper.step(false);  // true = sens horaire
  }

  delay(2000);

  Serial.print("Position finale (devrait être la même que la position de départ) : ");
  Serial.println(stepper.getStep());
}

/* ----- Fin : FONCTIONS DE TESTS DES COMPOSANTS ----- */

void fonctionTest_TemperatureSensor()
{
  float t = tcn.readTemperature();
  
  Serial.println("Temperature : ");
  Serial.println(t);
  delay(500);
}

void fonctionTest_MoteurPasAPas()
{
  // Placer le moteur à la position de départ (960)
  stepper.moveTo(true, position_defaut);
  Serial.print("Position initiale définie à : ");
  Serial.println(stepper.getStep());

  // Rotation de 180° (2048 pas) dans un sens (CW)
  Serial.println("Rotation de 180° dans le sens horaire (CW)...");
  for (int s = 0; s < 2048; s++) {
    stepper.step(true);  // Sens horaire
    if (stepper.getStep() % 64 == 0) {  // Affichage périodique
      Serial.print("Position actuelle : ");
      Serial.println(stepper.getStep());
    }
  }

  delay(1000);  // Pause

  // Retour à la position 960 en sens inverse 
  Serial.println("Retour à la position initiale ...");
  for (int s = 0; s < 2048; s++) {
    stepper.step(false);  // Sens antihoraire
    if (stepper.getStep() % 64 == 0) {
      Serial.print("Position actuelle : ");
      Serial.println(stepper.getStep());
    }
  }

  // Vérification de la position finale
  Serial.print("Position finale après retour : ");
  Serial.println(stepper.getStep());

  delay(1000);  // Pause avant de terminer
}

void fonctionTest_Peltier(int valeur_PWM)
{
  analogWrite(pin_Peltier, valeur_PWM);
}

void fonctionTest_ResistanceChauffante(int valeur_PWM)
{
  analogWrite(pin_Resistance_Chauffante, valeur_PWM);
}

void fonctionTest_Soleil(int valeur_PWM)
{
  analogWrite(pin_Soleil, valeur_PWM);
}

void fonctionTest_Ventilateur(int valeur_PWM)
{
  analogWrite(pin_Ventilateur, valeur_PWM);
}

void fonctionTest_Lcd()
{
  lcd.backlight();
  lcd.clear();
  // Envoi du message sur le LCD
  lcd.setCursor(0,0);
  lcd.print("Test");
  lcd.setCursor(1,1);
  lcd.print("du");
  lcd.setCursor(2,2);
  lcd.print("LCD");
  lcd.setCursor(3,0);
  lcd.print("Test I2C");
}

void fonctionTest_Led()
{
  digitalWrite(pin_Led_Hiver, HIGH);
  delay(200);
  digitalWrite(pin_Led_Hiver, LOW);
  delay(200);

  digitalWrite(pin_Led_Ete, HIGH);
  delay(200);
  digitalWrite(pin_Led_Ete, LOW);
  delay(200);
}

void fonctionTest_Bouton()
{
  if(digitalRead(pin_Bouton_Hiver) == LOW)
  {
    Serial.println("Bouton_Hiver : LOW");
  }
  if(digitalRead(pin_Bouton_Ete) == LOW)
  {
    Serial.println("Bouton_Ete : LOW");
  }
}

void fonctionTest_Potentiometre()
{
  int p = analogRead(pin_Potentiometre);
  int positon_Potentiometre = p/4;

  Serial.println("position_Potentiometre : ");
  Serial.println(positon_Potentiometre);
  delay(50);
}
