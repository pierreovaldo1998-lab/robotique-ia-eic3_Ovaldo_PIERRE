/*
  Devoir 3 - Bras robotique à 3 degrés de liberté (Arduino Uno, Tinkercad)
  3 servomoteurs = 3 articulations rotoïdes en chaîne ouverte (RRR)
    - servoBase     (D9)  : rotation autour de l'axe vertical (lacet)
    - servoEpaule   (D10) : élévation du bras
    - servoCoude    (D11) : flexion de l'avant-bras

  Analogie avec le langage VAL3 (Stäubli) vu en cours :
    - une pose = un "joint" (angles des articulations)  -> struct Pose
    - movej(pose, vitesse)                              -> moveToPose()
    - sequence dans begin() ... end()                   -> loop()
*/
#include <Servo.h>

// ---------- Broches ----------
const int PIN_BASE   = 9;
const int PIN_EPAULE = 10;
const int PIN_COUDE  = 11;

// ---------- Limites articulaires (équivalent "Arm Limits") ----------
const int ANGLE_MIN = 10;
const int ANGLE_MAX = 170;

// ---------- Poses (angles en degrés) : "joint locations" ----------
struct Pose { int base; int epaule; int coude; };
const Pose POSE_REPOS  = {90,  90,  90};   // jSafe
const Pose POSE_PRISE  = {30, 120,  60};   // jPick
const Pose POSE_DEPOT  = {150, 70, 130};   // jPlace

// ---------- Paramètres de mouvement ----------
const int  VITESSE_PCT = 50;   // 1..100 : équivalent d'une vitesse en % (mdesc.vel)
const int  PAUSE_MS    = 800;  // temps d'arrêt aux poses (équivalent waitEndMove + pause)

Servo servoBase, servoEpaule, servoCoude;
Pose  poseCourante = POSE_REPOS;

int limiter(int a) { return constrain(a, ANGLE_MIN, ANGLE_MAX); }

// Mouvement articulaire coordonné : toutes les articulations arrivent en même temps
// (interpolation linéaire dans l'espace des articulations, comme movej).
void moveToPose(const Pose &cible, int vitessePct) {
  int dB = limiter(cible.base)   - poseCourante.base;
  int dE = limiter(cible.epaule) - poseCourante.epaule;
  int dC = limiter(cible.coude)  - poseCourante.coude;
  int n  = max(abs(dB), max(abs(dE), abs(dC)));      // nombre de pas = plus grand déplacement
  int delaiMs = map(constrain(vitessePct, 1, 100), 1, 100, 40, 3);  // + vite = + court

  for (int i = 1; i <= n; i++) {
    servoBase.write  (poseCourante.base   + (long)dB * i / n);
    servoEpaule.write(poseCourante.epaule + (long)dE * i / n);
    servoCoude.write (poseCourante.coude  + (long)dC * i / n);
    delay(delaiMs);
  }
  poseCourante = {limiter(cible.base), limiter(cible.epaule), limiter(cible.coude)};
  Serial.print("Pose atteinte -> base=");   Serial.print(poseCourante.base);
  Serial.print(" epaule=");                 Serial.print(poseCourante.epaule);
  Serial.print(" coude=");                  Serial.println(poseCourante.coude);
}

void setup() {
  Serial.begin(9600);
  servoBase.attach(PIN_BASE);
  servoEpaule.attach(PIN_EPAULE);
  servoCoude.attach(PIN_COUDE);
  servoBase.write(POSE_REPOS.base);
  servoEpaule.write(POSE_REPOS.epaule);
  servoCoude.write(POSE_REPOS.coude);
  delay(1000);
}

void loop() {
  // Séquence type pick & place : repos -> prise -> dépôt -> repos
  moveToPose(POSE_REPOS, VITESSE_PCT); delay(PAUSE_MS);
  moveToPose(POSE_PRISE, VITESSE_PCT); delay(PAUSE_MS);
  moveToPose(POSE_DEPOT, VITESSE_PCT); delay(PAUSE_MS);
  moveToPose(POSE_REPOS, VITESSE_PCT); delay(2000);
}
