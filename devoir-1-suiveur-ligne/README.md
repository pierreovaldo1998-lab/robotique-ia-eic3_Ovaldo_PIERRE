# Devoir 1 — Robot suiveur de ligne

## 1. Objectif
Programmer le robot virtuel VEXcode VR pour qu'il suive automatiquement une ligne tracée au sol,
sans intervention, en corrigeant sa direction à partir de la mesure du capteur.
**Critère de réussite :** le robot parcourt tout le tracé du terrain « Line Tracking » sans quitter la ligne.

## 2. Outils et composants
| Élément | Rôle | Classification (cours) |
|---|---|---|
| VEXcode VR (Python) — https://vr.vex.com | Environnement de simulation et de programmation | — |
| Terrain « Line Tracking » | Environnement du robot | — |
| `down_eye` (capteur de couleur/luminosité vers le sol) | Mesure de la position du robot par rapport à la ligne | Capteur **extéroceptif** ; **actif** (il éclaire la surface) |
| `left_motor`, `right_motor` | Actionneurs de la locomotion différentielle | Actionneurs |

## 3. Fonctionnement
**Principe : suivi de bord avec correcteur proportionnel.**
Le capteur ne voit pas « la ligne » mais une luminosité. Au lieu d'exiger que le robot soit centré sur la ligne
(ce qui ne permet pas de savoir de quel côté on dérive), on lui fait suivre le **bord** de la ligne :

- consigne `TARGET` = moyenne entre la luminosité de la ligne et celle du sol ;
- erreur = `TARGET − mesure` ; le signe indique de quel côté du bord on se trouve ;
- correction = `KP × erreur`, ajoutée à la vitesse d'un moteur et retranchée à celle de l'autre.

C'est une **boucle fermée** : mesure → comparaison à la consigne → commande → effet sur le robot → nouvelle mesure
(architecture capteurs / contrôle / actionneurs vue en cours).

Paramètres :
- `BASE_SPEED` : vitesse de croisière ; trop élevée, le robot « décroche » dans les virages.
- `KP` : trop faible, le robot tourne trop tard ; trop élevé, il oscille (zigzag).
- Fréquence de la boucle : 50 Hz (20 ms). Le capteur et la boucle doivent être assez rapides par rapport à la dynamique du robot
  (notion de bande passante / temps de réponse d'un capteur).

### Calibration (à faire avant l'essai)
1. Placer le robot sur la ligne, afficher `down_eye.brightness()` → noter `BRIGHT_LINE`.
2. Le placer sur le sol → noter `BRIGHT_FLOOR`.
3. Régler `KP` : commencer à 0,3 et augmenter jusqu'à apparition de légères oscillations, puis redescendre de 20 %.
4. Si le robot s'éloigne de la ligne au lieu de la suivre, inverser le signe de `correction`.

> ℹ️ Les noms d'objets (`down_eye`, `left_motor`…) et le nom exact du terrain peuvent varier légèrement selon
> la version de VEXcode VR : vérifier dans la boîte à outils de l'application.

## 4. Résultats
> À compléter après l'essai.

| Essai | BASE_SPEED | KP | Résultat observé | Temps de parcours |
|---|---|---|---|---|
| 1 | 40 | 0,30 | [À COMPLÉTER] | [ ] |
| 2 | 40 | 0,45 | [À COMPLÉTER] | [ ] |
| 3 | 60 | 0,45 | [À COMPLÉTER] | [ ] |

Captures : `captures/01_robot_sur_ligne.png`, `captures/02_programme.png`

## 5. Analyse
- Compromis **vitesse / stabilité** : le gain et la vitesse doivent être ajustés ensemble.
- **Limites** : sensible à la calibration (luminosité) ; le correcteur P seul laisse des oscillations et perd la ligne dans les virages serrés.
- **Améliorations** : ajouter un terme dérivé (PD) ; ralentir quand l'erreur est grande ; stratégie de récupération si la ligne est perdue
  (balayage gauche/droite).
