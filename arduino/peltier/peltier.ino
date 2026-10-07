// Broche de contrôle PWM du module Peltier
const int peltierPin = 5;  

void setup() {
  Serial.begin(9600);             // Initialisation la communication série
  pinMode(peltierPin, OUTPUT);    // Définition du pin comme sortie
  Serial.println("Envoie un chiffre de 1 à 5 pour régler la puissance du Peltier :");
  Serial.println("1 = 20%, 2 = 40%, 3 = 60%, 4 = 80%, 5 = 100%");
}

void loop() {
  if (Serial.available() > 0) {
    char caractere = Serial.read();  // Lécture du caractère reçu en entrée

    // Initialisation de la variable PWM
    int pwmValue = 0;

    // Les choix en fonction du caractère reçu
    if (caractere == '1') {
      pwmValue = 51;  // 20% de 255
      analogWrite(peltierPin, pwmValue);  // Application du signal PWM
    } else if (caractere == '2') {
      pwmValue = 102; // 40%
      analogWrite(peltierPin, pwmValue);

    } else if (caractere == '3') {
      pwmValue = 153; // 60%
      analogWrite(peltierPin, pwmValue);
    } else if (caractere == '4') {
      pwmValue = 204; // 80%
      analogWrite(peltierPin, pwmValue);
    } else if (caractere == '5') {
      pwmValue = 255; // 100%
      analogWrite(peltierPin, pwmValue);
    } else {
      Serial.println("Commande invalide, envoie 1 à 5.");
      return;
    }

    Serial.print("PWM réglé à : ");
    Serial.println(pwmValue);
  }
}
