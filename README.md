# Robotique & Intelligence Artificielle — EIC 3.0

**Étudiant(e) :** [Prénom NOM]  
**Formateur :** Carlos Yfrazin, Ingénieur Électricien  
**Remise :** mardi 13 octobre 2026, 23 h 59 (heure d'Haïti)

Ce dépôt regroupe les six devoirs pratiques de la formation. Chaque projet a son dossier,
avec son code, ses captures d'écran et un `README.md` (objectif, outils, fonctionnement, résultats).

## Projets

| # | Dossier | Plateforme | Thème du cours mobilisé |
|---|---------|-----------|--------------------------|
| 1 | [`devoir-1-suiveur-ligne`](devoir-1-suiveur-ligne) | VEXcode VR | Capteur optique, boucle de commande (asservissement) |
| 2 | [`devoir-2-evitement-obstacles`](devoir-2-evitement-obstacles) | VEXcode VR | Capteur de distance (temps de vol), évitement d'obstacles |
| 3 | [`devoir-3-bras-robotique`](devoir-3-bras-robotique) | Tinkercad + Arduino Uno | Degrés de liberté, articulations rotoïdes, `movej` |
| 4 | [`devoir-4-classificateur-images`](devoir-4-classificateur-images) | Teachable Machine (image) | Apprentissage supervisé, capteur passif (caméra) |
| 5 | [`devoir-5-classificateur-sons`](devoir-5-classificateur-sons) | Teachable Machine (audio) | Apprentissage supervisé, capteur passif (microphone) |
| 6 | [`devoir-6-decision-esp32`](devoir-6-decision-esp32) | Wokwi + ESP32 | Chaîne capteur → décision → actionneur |

## Démarche commune

Les six projets suivent la même méthode, issue de l'architecture fonctionnelle d'un robot
vue en cours (capteurs → traitement/décision → actionneurs) :

1. **Spécifier** : objectif mesurable et critère de réussite.
2. **Modéliser** : identifier capteurs, actionneurs, grandeur à mesurer, seuils ou paramètres.
3. **Implémenter** : code commenté, paramètres regroupés en tête de fichier.
4. **Valider** : essai en simulation, capture d'écran, observation des cas limites.
5. **Analyser** : limites constatées, pistes d'amélioration.

## Sources

- F. Morbidi, *Initiation à la Robotique*, Licence Pro Automatisme et Robotique, UPJV (supports de cours fournis).
- R. Siegwart, I. Nourbakhsh, D. Scaramuzza, *Introduction to Autonomous Mobile Robots*, 2e éd., MIT Press
  (chap. 4 : perception ; chap. 6 : planification et évitement d'obstacles).
- Documentation officielle : VEXcode VR, Tinkercad Circuits, Google Teachable Machine, Wokwi.

## Remarque d'honnêteté académique

Les captures d'écran et les résultats chiffrés ont été obtenus lors de mes propres essais.
Le code a été rédigé à partir des notions du cours ; les paramètres (seuils, gains) ont été calibrés par expérimentation.
