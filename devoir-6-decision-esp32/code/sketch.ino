/*
  Devoir 6 - Robot à décision intelligente (ESP32, Wokwi)
  Capteur  : HC-SR04 (ultrasons, temps de vol)   d = 1/2 * v * t
  Décision : seuils avec hystérésis -> 3 niveaux (SÛR / ATTENTION / DANGER)
  Actions  : LED (clignotante ou fixe), buzzer, message série
*/
const int PIN_TRIG   = 5;
const int PIN_ECHO   = 18;
const int PIN_LED    = 4;
const int PIN_BUZZER = 15;

// ----- Paramètres -----
const float SEUIL_DANGER_CM    = 30.0;   // < 30 cm : LED fixe + buzzer
const float SEUIL_ATTENTION_CM = 60.0;   // < 60 cm : LED clignote
const float HYSTERESIS_CM      = 3.0;    // évite le "battement" autour d'un seuil
const int   NB_MESURES         = 5;      // médiane de 5 mesures (réduit le bruit)
const unsigned long TIMEOUT_US = 30000;  // ~5 m aller-retour : au-delà, pas d'écho
const float VITESSE_SON_CM_US  = 0.0343; // 343 m/s à 20 °C -> 0,0343 cm/µs

enum Niveau { SUR, ATTENTION, DANGER };
Niveau niveau = SUR;

float mesureUneFois() {
  digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  unsigned long t = pulseIn(PIN_ECHO, HIGH, TIMEOUT_US);   // durée aller-retour (µs)
  if (t == 0) return -1.0;                                  // pas d'écho
  return t * VITESSE_SON_CM_US / 2.0;                       // d = 1/2 v t
}

float mesureFiltree() {
  float v[NB_MESURES]; int n = 0;
  for (int i = 0; i < NB_MESURES; i++) { float d = mesureUneFois(); if (d > 0) v[n++] = d; delay(15); }
  if (n == 0) return -1.0;
  for (int i = 1; i < n; i++) { float k = v[i]; int j = i - 1; while (j >= 0 && v[j] > k) { v[j+1] = v[j]; j--; } v[j+1] = k; }
  return v[n / 2];   // médiane
}

Niveau decider(float d, Niveau courant) {
  if (d < 0) return SUR;   // aucun écho : rien dans la portée
  // hystérésis : le seuil de sortie est plus éloigné que le seuil d'entrée
  if (courant == DANGER)    { if (d < SEUIL_DANGER_CM + HYSTERESIS_CM) return DANGER; }
  if (d < SEUIL_DANGER_CM)  return DANGER;
  if (courant == ATTENTION) { if (d < SEUIL_ATTENTION_CM + HYSTERESIS_CM) return ATTENTION; }
  if (d < SEUIL_ATTENTION_CM) return ATTENTION;
  return SUR;
}

void agir(Niveau n) {
  switch (n) {
    case SUR:       digitalWrite(PIN_LED, LOW);  noTone(PIN_BUZZER); break;
    case ATTENTION: digitalWrite(PIN_LED, (millis() / 250) % 2); noTone(PIN_BUZZER); break;
    case DANGER:    digitalWrite(PIN_LED, HIGH); tone(PIN_BUZZER, 1000); break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT); pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED, OUTPUT);  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  float d = mesureFiltree();
  niveau = decider(d, niveau);
  agir(niveau);
  Serial.print("Distance = "); if (d < 0) Serial.print("hors portee"); else { Serial.print(d, 1); Serial.print(" cm"); }
  Serial.print(" | niveau = ");
  Serial.println(niveau == SUR ? "SUR" : niveau == ATTENTION ? "ATTENTION" : "DANGER");
  delay(60);
}
