# Devoir 6 — Robot à décision intelligente (ESP32)

## 1. Objectif
Construire un système ESP32 qui **prend une décision automatique selon un seuil mesuré par un capteur** : si la valeur dépasse le seuil, une action est déclenchée.

**Choix du capteur : distance (HC-SR04, ultrasons).** Justification : c'est un capteur de télémétrie active par temps de vol, exactement celui étudié en cours, et la fonction « détecter un obstacle proche » est centrale en robotique mobile.

🔗 **Lien du projet Wokwi :** [À COLLER ICI après *Save*]

## 2. Composants
| Composant | Broche ESP32 | Rôle |
|---|---|---|
| ESP32 DevKit | — | Calculateur |
| HC-SR04 | TRIG → GPIO 5, ECHO → GPIO 18, VCC → VIN (5 V), GND | Capteur extéroceptif actif (distance) |
| LED rouge + résistance 220 Ω | GPIO 4 | Signal visuel |
| Buzzer | GPIO 15 | Signal sonore |

> `code/diagram.json` peut être collé dans l'onglet *diagram.json* de Wokwi ; si le câblage s'affiche mal, le refaire à la main d'après ce tableau.

## 3. Fonctionnement
**Chaîne capteur → décision → actionneur** (architecture capteurs / contrôle / actionneurs vue en cours).

1. **Mesure** : impulsion de 10 µs sur TRIG, mesure de la durée de l'écho `t` (aller-retour).
2. **Calcul** : `d = ½ · v · t` avec `v = 343 m/s` (0,0343 cm/µs à 20 °C). Le cours utilise ≈ 300 m/s comme ordre de grandeur ; la vitesse du son dépend du milieu (température).
3. **Filtrage** : médiane de 5 mesures pour réduire le bruit (notion de **précision/reproductibilité** d'un capteur).
4. **Décision** (3 niveaux) avec **hystérésis** de 3 cm :

| Distance | Niveau | Action |
|---|---|---|
| ≥ 60 cm ou pas d'écho | SÛR | LED éteinte, buzzer muet |
| 30–60 cm | ATTENTION | LED clignote |
| < 30 cm | DANGER | LED fixe + buzzer + message série |

Pourquoi l'hystérésis ? Sans elle, une mesure qui oscille autour de 30 cm ferait basculer l'état en permanence. Le seuil de sortie est donc plus éloigné que le seuil d'entrée.

Pourquoi un *timeout* ? Certaines surfaces **absorbent** le son ou le **réfléchissent hors de l'axe** (réflexion spéculaire) : l'écho ne revient jamais ; le programme doit gérer ce cas (cours, « Exemple : sonar », problèmes pratiques).

**Lien avec la sécurité (cours).** Le boîtier d'apprentissage d'un robot industriel impose l'arrêt immédiat à l'appui sur l'arrêt d'urgence ou au relâchement de l'interrupteur de corps mort. Le niveau DANGER de ce projet en est l'analogue : une condition de proximité prend le pas sur la tâche en cours.

## 4. Résultats
> À compléter après simulation (faire glisser le curseur de distance du HC-SR04 dans Wokwi).

| Distance réglée | Niveau attendu | LED | Buzzer | Observé |
|---|---|---|---|---|
| 100 cm | SÛR | éteinte | non | [ ] |
| 45 cm | ATTENTION | clignote | non | [ ] |
| 20 cm | DANGER | fixe | oui | [ ] |
| 32 cm (en descendant depuis 20) | DANGER (hystérésis) | fixe | oui | [ ] |

Captures : `captures/01_circuit.png`, `captures/02_danger.png`, `captures/03_moniteur_serie.png`

## 5. Analyse
- **Limites** : le HC-SR04 est dans le cône du faisceau (angle d'ouverture non nul) et sa portée utile est de quelques centimètres à ≈ 4 m ; la vitesse du son varie avec la température.
- **Améliorations** : compensation en température (DHT22) ; sortie PWM proportionnelle à la distance ; connecter la décision à un moteur (arrêt du robot) ; fusion avec un second capteur.
