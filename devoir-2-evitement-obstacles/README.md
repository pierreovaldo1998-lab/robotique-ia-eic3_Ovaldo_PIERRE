# Devoir 2 — Robot évitant les obstacles

## 1. Objectif
Programmer le robot virtuel pour qu'il **détecte un obstacle** avec un capteur de distance, **s'arrête, tourne**,
puis **continue** sa route automatiquement.
**Critère de réussite :** le robot traverse le terrain à obstacles sans collision.

## 2. Outils et composants
| Élément | Rôle | Classification (cours) |
|---|---|---|
| VEXcode VR (Python) + terrain avec obstacles (ex. « Obstacle Course ») | Simulation | — |
| `front_distance` | Mesure de la distance à l'obstacle | Capteur **extéroceptif actif**, télémétrie par **temps de vol** |
| `drivetrain` | Avance et rotation | Actionneurs |

## 3. Fonctionnement
**Lien avec le cours.** Un télémètre actif émet une onde et mesure le temps d'aller-retour : `d = ½ · v · t`
(sonar : vitesse du son ≈ 300 m/s ; laser : vitesse de la lumière). La mesure est exploitée ici pour une
**navigation réactive** (Siegwart et al., chap. 6.2.2 : *obstacle avoidance*, qui module la trajectoire à partir
de mesures en temps réel).

**Algorithme (machine à deux états) :**
```
BOUCLE
  si distance < SEUIL :  AVOIDER
  sinon :                AVANCER
FIN

AVOIDER : stop → tourner à droite 90° → mesurer → tourner à gauche 180° → mesurer
          → s'orienter vers le côté le plus dégagé
```
- Le **seuil** (250 mm) doit tenir compte de la distance d'arrêt du robot et de la portée utile du capteur.
- Le robot **regarde des deux côtés** avant de choisir, ce qui évite de tourner vers un mur.

## 4. Résultats
> À compléter après l'essai.

| Terrain | SEUIL (mm) | Collisions | Observations |
|---|---|---|---|
| [À COMPLÉTER] | 250 | [ ] | [ ] |

Captures : `captures/01_evitement.png`, `captures/02_programme.png`

## 5. Analyse
- **Limites** : un seul capteur frontal (champ de vue étroit) ; les obstacles latéraux ne sont pas vus pendant la rotation ;
  une impasse (cul-de-sac) peut provoquer des allers-retours.
- **Améliorations** : capteurs latéraux ; mémoriser le dernier côté choisi ; algorithme de type **Bug** (Siegwart, 6.2.2.1),
  qui suit le contour de l'obstacle jusqu'à retrouver la direction du but.
