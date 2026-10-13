# Devoir 3 — Bras robotique à plusieurs degrés de liberté

## 1. Objectif
Construire dans Tinkercad un petit bras à **3 servomoteurs** piloté par un Arduino Uno, et le programmer pour
qu'il rejoigne des **positions précises** en séquence (repos → prise → dépôt → repos).

## 2. Outils et composants
| Composant | Quantité | Rôle |
|---|---|---|
| Arduino Uno | 1 | Contrôleur |
| Micro servomoteur | 3 | Actionneurs (une articulation chacun) |
| Fils, plaque d'essai | — | Câblage |

**Câblage :** pour chaque servo : fil marron/noir → GND ; rouge → 5 V ; orange/jaune (signal) → D9, D10, D11.
> Sur du matériel réel, alimenter les servos par une source externe (leur courant dépasse ce que fournit le 5 V de l'Arduino) et relier les masses.

## 3. Degrés de liberté et rôle de chaque servomoteur
D'après le cours : un DDL est « la capacité à se mouvoir selon un axe de translation ou de rotation » ;
dans une chaîne ouverte, chaque articulation rotoïde ou prismatique apporte **un seul** DDL.

| Servo | Broche | Articulation | Rôle | Axe |
|---|---|---|---|---|
| Base | D9 | Rotoïde R1 | Oriente le bras dans le plan horizontal (balayage) | Vertical |
| Épaule | D10 | Rotoïde R2 | Lève/abaisse l'ensemble du bras | Horizontal |
| Coude | D11 | Rotoïde R3 | Fléchit l'avant-bras, règle la portée | Horizontal |

**Nombre de DDL = 3 (structure RRR, chaîne ouverte).**

**Ce que 3 DDL permettent — et ne permettent pas.** Trois DDL suffisent à placer l'extrémité du bras en un point de son espace de travail
(3 coordonnées de position). Ils ne permettent **pas** d'orienter librement l'outil. Selon le cours, positionner **et**
orienter arbitrairement un objet dans l'espace 3D exige **6 DDL** (3 de position + 3 d'orientation), ce qui explique que le
Stäubli TX60 ait 6 axes. Le bras réalisé ici est donc **non redondant** et **sous-actionné** par rapport à une tâche de pose complète.

## 4. Fonctionnement du programme
Le code reprend la logique de programmation d'un robot industriel (Stäubli / VAL3) :

| Notion du cours (VAL3) | Équivalent dans le code |
|---|---|
| Variable `joint` (positions articulaires) | `struct Pose` : `POSE_REPOS`, `POSE_PRISE`, `POSE_DEPOT` |
| `movej(pose, outil, mdesc)` | `moveToPose(pose, vitesse)` |
| `mdesc.vel` (vitesse en %) | `VITESSE_PCT` |
| Limites articulaires (*Arm limits*) | `ANGLE_MIN` / `ANGLE_MAX` + `constrain()` |
| Programme `begin … end` | `loop()` |

`moveToPose` effectue une **interpolation linéaire dans l'espace articulaire** : les trois servos reçoivent un angle intermédiaire
à chaque pas, et arrivent **simultanément** à la cible. Les angles sont lus dans le **moniteur série** (9600 bauds) à chaque pose atteinte.

## 5. Résultats
> À compléter après la simulation.
- Séquence observée : [À COMPLÉTER]
- Angles lus au moniteur série : [À COMPLÉTER]
- Captures : `captures/01_circuit.png`, `captures/02_simulation.png`, `captures/03_moniteur_serie.png`

## 6. Analyse
- **Précision** : un servo standard a une résolution de 1° ; l'erreur au bout du bras croît avec la longueur (`erreur ≈ L · Δθ`).
  À distinguer de la **répétabilité** (capacité à revenir au même point), seule caractéristique garantie par les fabricants (±0,02 mm pour le TX60).
- **Limites** : pas de capteur de position (commande en boucle ouverte) ; pas de modèle géométrique direct/inverse — les poses sont
  données en angles, pas en coordonnées cartésiennes.
- **Améliorations** : modèle géométrique inverse pour viser un point (x, y, z) ; ajout d'un 4ᵉ servo (pince) ; profil de vitesse trapézoïdal.
