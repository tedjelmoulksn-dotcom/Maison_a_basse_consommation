/* -------------------------------------------------------------------------------------------
| PROJET INSTRUMENTATION : Greg ALBERTS, Sarah DAHMOUN, Hugo LEBAUD, Tedj El Moulk SINACER   |
------------------------------------------------------------------------------------------- */

#include <Wire.h>   // library used with I2C protocol
#include "TCN75A.h"
#include <LiquidCrystal_I2C.h> // Nécessite l'installation de la bibliothèque LiquidCrystal_I2C 
                               //dans le gestionnaire de bibliothèque intégré à Arduino IDE

int pin_Peltier = 3;
int pin_Resistance_Chauffante = 4;
int pin_Soleil = 5;
int pin_Ventilateur = 6;
int pin_Bouton_Hiver = 7;
int pin_Bouton_Ete = 8;
int pin_Led_Hiver = 9;
int pin_Led_Ete = 10;
int pin_Potentiometre = 11;

TCN75A tcn(0x48);
LiquidCrystal_I2C lcd(0x27, 20, 4);

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
}

void loop() {
  // fonctionTest_TemperatureSensor();
  // fonctionTest_MoteurPasAPas();
  // fonctionTest_Peltier(255);
  // fonctionTest_ResistanceChauffante(255);
  // fonctionTest_Soleil(255);
  // fonctionTest_Ventilateur(255);
  // fonctionTest_Lcd();
  // fonctionTest_Led();
  // fonctionTest_Bouton();
  // fonctionTest_Potentiometre();
}

/* ----- Début : FONCTIONS DU PROJET ----- */

// Fonction permettant selon le composant, de lui envoyer une commande PWM
void fonctionProjet_PWM(char* nom_composant, int valeur_PWM)
{
  if(nom_composant == "PELTIER")
  {
    analogWrite(pin_Peltier, valeur_PWM);
  }
  else if(nom_composant == "RESISTANCE")
  {
    analogWrite(pin_Resistance_Chauffante, valeur_PWM);
  }
  else if(nom_composant == "SOLEIL")
  {
    analogWrite(pin_Soleil, valeur_PWM);
  }
  else if(nom_composant == "VENTILATEUR")
  {
    analogWrite(pin_Ventilateur, valeur_PWM);
  }
}

// Fonction permettant de lire la température intérieure grâce au capteur
void fonctionProjet_TemperatureSensor()
{
  float t = tcn.readTemperature();
  
  Serial.println("Temperature : ");
  Serial.println(t);
  delay(500);
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
  
  // Envoi du message sur le LCD
  lcd.setCursor(0,0);
  lcd.print("Test");
  lcd.setCursor(1,5);
  lcd.print("du");
  lcd.setCursor(2,15);
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