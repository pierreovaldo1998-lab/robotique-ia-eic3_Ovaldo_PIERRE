# Devoir 5 — Classificateur de sons

## 1. Objectif
Entraîner un modèle d'IA à **reconnaître 2 ou 3 sons** (microphone), le tester en direct, puis le **comparer** au classificateur d'images du devoir 4.

## 2. Outils
- Google Teachable Machine → *Audio Project*.
- Microphone (autoriser l'accès dans le navigateur). Environnement le plus silencieux possible.
- `code/index.html` : page de test du modèle exporté.

## 3. Protocole suivi
1. Classes : **Bruit de fond** (obligatoire dans Teachable Machine, ≥ 20 échantillons de 2 s), **[Son A : mot « ___ »]**, **[Son B : claquement de mains]**.
2. Enregistrement : plusieurs échantillons de 1 s par classe (j'en ai pris : [__] ; viser ≥ 20 pour plus de robustesse), avec variations (distance au micro, intensité, voix).
3. *Train Model* (paramètres par défaut). 4. Test en direct, en incluant des sons non appris. 5. Export du modèle (facultatif) et test via `code/index.html`.

## 4. Fonctionnement
Le son n'est pas donné tel quel au réseau : il est converti en **spectrogramme** (analyse fréquentielle de type FFT : énergie par fréquence au cours du temps),
c'est-à-dire en une **image temps × fréquence**. Le principe d'apprentissage supervisé est ensuite le même que pour les images : exemples étiquetés → ajustement des poids → probabilité par classe.

## 5. Résultats
| Son testé | Classe prédite | Probabilité | OK ? |
|---|---|---|---|
| [Mot] | [ ] | [__] | [ ] |
| [Claquement] | [ ] | [__] | [ ] |
| Silence | Bruit de fond | [__] | [ ] |
| Son inconnu | ? | [__] | [ ] |

Captures : `captures/01_echantillons.png`, `captures/02_entrainement.png`, `captures/03_reconnaissance_reussie.png`

## 6. Comparaison avec le classificateur d'images (devoir 4)

| Aspect | Similitudes | Différences |
|---|---|---|
| **Méthode** | Apprentissage supervisé : exemples étiquetés → modèle ; mêmes étapes (classes, échantillons, entraînement, test, export) | — |
| **Modèle** | Réseau de neurones avec transfert d'apprentissage ; sortie = probabilités par classe | Images : réseau pré-entraîné sur des photos. Sons : modèle pré-entraîné sur des commandes vocales courtes |
| **Données d'entrée** | Capteur **passif extéroceptif** dans les deux cas (caméra / microphone, cf. classification des capteurs du cours) | Image : matrice de pixels fixe. Son : **signal temporel** converti en spectrogramme ; durée fixe de 1 s |
| **Classe de fond** | Utile dans les deux cas | **Obligatoire** pour les sons (bruit de fond), facultative mais recommandée pour les images |
| **Sensibilité** | Dépend de la qualité et de la diversité des données | Images : éclairage, arrière-plan. Sons : bruit ambiant, distance au micro, accent/voix |
| **Usage en direct** | Prédiction continue | Son : prédiction par fenêtres glissantes (chevauchement) |

**Lecture robotique.** Image et son sont deux modalités de perception ; un robot pourrait les fusionner. Contrairement aux capteurs **actifs** de télémétrie (sonar, laser :
le capteur émet puis mesure l'écho), le microphone ne fait que **recevoir** des signaux émis par l'environnement.

## 7. Analyse
- Le modèle confond facilement deux sons de même spectre ; plus d'échantillons variés améliorent la robustesse.
- Le **seuil de probabilité** conditionne le compromis entre fausses détections et détections manquées.
