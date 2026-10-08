#include <Adafruit_CircuitPlayground.h>


  int game = 0;
  int choice = 0;
  int winner = 0;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  CircuitPlayground.setBrightness(15);
  winner = random(1,3);
}

void loop() {
  // -------------------------------------------------------------
  // 1. ÉTAT EN ATTENTE 
  // -------------------------------------------------------------
  if (game == 0) {
    animationRainbow();

    // Détection du Bouton A (Choix ROUGE)
    if (CircuitPlayground.leftButton()) {
      choice = 1; // 1 correspond au Rouge
      game = 1;
      
      // Animation de sélection : Clignotement ROUGE (3 fois)
      clignoterCouleur(255, 0, 0);
    } 
    // Détection du Bouton B (Choix BLANC)
    else if (CircuitPlayground.rightButton()) {
      choice = 2; // 2 correspond au Blanc
      game = 1;
      
      // Animation de sélection : Clignotement BLANC (3 fois)
      clignoterCouleur(0, 0, 255);
    }
  }

  // -------------------------------------------------------------
  // 2. RÉSOLUTION DU JEU (Après sélection d'une couleur)
  // -------------------------------------------------------------
  if (game == 1) {
    delay(200);

    // Animation de transition / suspense (4 tours)
    for (int i = 0; i < 4; i++) {
      animationColorWipe();
    }

    // Vérification du résultat
    if (choice == winner) {
      // VICTOIRE
      CircuitPlayground.clearPixels();
      sonMcDonalds();
      animationSparkle();
      delay(2000);
    } else {
      // DÉFAITE
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(10, 238, 130, 238); // Violet
      sonDefaite();
      delay(2000);
    }

    // Réinitialisation pour la partie suivante
    choice = 0;
    game = 0;
    winner = random(1, 3); // Nouveau gagnant aléatoire (1 ou 2)
  }
}
























// =============================================================
// --- ANIMATIONS & EFFETS ---
// =============================================================

// Clignotement de la couleur sélectionnée
void clignoterCouleur(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 3; i++) { // Clignote 3 fois
    // Allumer toutes les LED
    for (int j = 0; j < 10; j++) {
      CircuitPlayground.setPixelColor(j, r, g, b);
    }
    sonSelection();
    delay(200);

    // Éteindre
    CircuitPlayground.clearPixels();
    delay(200);
  }
}

// Animation d'attente
void animationRainbow() {
  


          for(int rgb = 255; rgb >= 0; rgb -= 5){
            if(CircuitPlayground.rightButton() || CircuitPlayground.leftButton()){
  return;
  }

              for (int i = 0; i < 10; i++) {
                CircuitPlayground.setPixelColor(i, rgb, rgb, rgb);
              }
              Serial.println(rgb);
              Serial.println("-----------");

              delay(25);
            }




  for(int rgb = 0; rgb <= 255; rgb += 5){
    if(CircuitPlayground.rightButton() || CircuitPlayground.leftButton()){
  return;
  }
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, rgb, rgb, rgb);
    }
    Serial.println(rgb);
    Serial.println("-----------");

    delay(25);
  }
}

void animationColorWipe() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 0); // Remplissage jaune
    sonAttente();
    delay(150);
  }
  CircuitPlayground.clearPixels();
}


void animationSparkle() {
  unsigned long start = millis();
  while (millis() - start < 2000) {
    int p = random(10);
    CircuitPlayground.setPixelColor(p, 255, 255, 255);
    delay(50);
    CircuitPlayground.setPixelColor(p, 0, 0, 0);
  }
}

void lancerAnimationVictoire() {
  
  // --- PHASE 1 : EXPLOSION DE CONFETTIS (SPARKLE) ---
  // Les LED scintillent de couleurs vives aléatoirement pendant 1.5 seconde.
  for (int i = 0; i < 50; i++) { // Répéter 50 cycles de scintillement
    
    for (int j = 0; j < 10; j++) { // Parcourir les 10 LED
      if (random(2) == 0) { // Allumer ou éteindre aléatoirement (50/50)
        
        // Choisir une couleur vive aléatoire
        int colorIndex = random(6);
        switch (colorIndex) {
          case 0: CircuitPlayground.strip.setPixelColor(j, 255, 0, 0); break;   // Rouge
          case 1: CircuitPlayground.strip.setPixelColor(j, 0, 255, 0); break;   // Vert
          case 2: CircuitPlayground.strip.setPixelColor(j, 0, 0, 255); break;   // Bleu
          case 3: CircuitPlayground.strip.setPixelColor(j, 255, 255, 0); break; // Jaune
          case 4: CircuitPlayground.strip.setPixelColor(j, 255, 0, 255); break; // Magenta
          case 5: CircuitPlayground.strip.setPixelColor(j, 0, 255, 255); break; // Cyan
        }
        
      } else {
        CircuitPlayground.strip.setPixelColor(j, 0, 0, 0); // Éteindre
      }
    }
    CircuitPlayground.strip.show(); // Appliquer les changements
    delay(30); // Vitesse du scintillement
  }
}
void sonSelection() {
  CircuitPlayground.playTone(880, 50); // Note La (A5) pendant 50ms
}
void sonVictoire() {
  // Notes : Do5, Mi5, Sol5, Do6
  CircuitPlayground.playTone(523, 100); 
  CircuitPlayground.playTone(659, 100); 
  CircuitPlayground.playTone(784, 100); 
  CircuitPlayground.playTone(1046, 300); // Note finale maintenue
}
void sonDefaite() {
  // Notes descendante avec un glissando vers le bas
  CircuitPlayground.playTone(400, 150);
  CircuitPlayground.playTone(350, 150);
  CircuitPlayground.playTone(300, 150);
  CircuitPlayground.playTone(200, 400); // Note grave traînante
}
void sonAttente() {
  // Un "tick" très court et grave
  CircuitPlayground.playTone(200, 15);
}

// -------------------------------------------------------------
// JINGLE MCDONALD'S (Rythmé & Syncopé)
// -------------------------------------------------------------
void sonMcDonalds() {
  int DO5  = 523;
  int RE5  = 587;
  int MI5  = 659;
  int SOL5 = 784;
  int LA5  = 880; // Correction : LA5 = 880 Hz (LA4 serait 440 Hz)

  // 1. "ba-da" (Do -> Ré)
  CircuitPlayground.playTone(DO5, 90);  delay(15);
  CircuitPlayground.playTone(RE5, 90);  delay(15);

  // 2. "ba" (Mi)
  CircuitPlayground.playTone(MI5, 140); delay(100);

  // 3. "-ba-" (La)
  CircuitPlayground.playTone(LA5, 180); delay(15);

  // 4. "-ba" (Sol - note finale)
  CircuitPlayground.playTone(SOL5, 500); delay(100);
}


