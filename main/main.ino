#include "buzzer.h" // Assure-toi que le fichier s'appelle bien comme ça

const int buzzerPin = 8;
RobotVoice compagnon(buzzerPin);

void setup() {
  // 1. Démarrer la communication série pour tes tests
  Serial.begin(9600);
  
  // 2. Initialiser le matériel du robot
  compagnon.begin();
  
  Serial.println("--- SYSTEME ROBOTIQUE STARHACK 2026 ---");
  
  // 3. Petite mélodie de démarrage (Axe Humain : Bienvenue)
  compagnon.playSequence("C4 E4 G4 C5"); 

  playFurElise();
}

void playFurElise() {
  // Partie 1 : Introduction
  compagnon.playSequence("E5 DS5 E5 DS5 E5 B4 D5 C5 A4");
  delay(100);
  compagnon.playSequence("C4 E4 A4 B4");
  delay(100);
  compagnon.playSequence("E4 GS4 B4 C5");
  
  // Partie 2 : Répétition avec variante
  delay(200);
  compagnon.playSequence("E5 DS5 E5 DS5 E5 B4 D5 C5 A4");
  delay(100);
  compagnon.playSequence("C4 E4 A4 B4");
  delay(100);
  compagnon.playSequence("E4 C5 B4 A4");

  // Partie 3 : La montée (Transition vers le milieu)
  delay(200);
  compagnon.playSequence("B4 C5 D5 E5 G4 F5 E5 D5 F4 E5 D5 C5 E4 D5 C5 B4");
}

void loop() {
  // Vérifier si tu as écrit quelque chose dans le moniteur série
  // if (Serial.available() > 0) {
  //   // Lire la chaîne de caractères jusqu'au retour à la ligne
  //   String commande = Serial.readStringUntil('\n');
  //   commande.trim(); // Nettoyer les espaces invisibles

  //   if (commande.length() > 0) {
  //     Serial.print("Le robot dit : ");
  //     Serial.println(commande);
      
  //     // Faire "parler" le robot
  //     compagnon.play(commande);
  //   }
  // }
  playFurElise();
}