# Devoir 4 — Classificateur d'images simple

## 1. Objectif
Entraîner un modèle d'IA à **reconnaître 2 ou 3 objets** grâce à la webcam, le tester en direct et expliquer ce qui se passe à l'entraînement.

## 2. Outils
- Google Teachable Machine (https://teachablemachine.withgoogle.com) → *Image Project*, *Standard image model*.
- Webcam. Navigateur web.
- `code/index.html` : page de test qui recharge le modèle exporté (export TensorFlow.js).

## 3. Protocole suivi
1. Création des classes : **[Classe 1 : ___]**, **[Classe 2 : ___]**, **[Classe 3 : « main vide / arrière-plan »]**.
2. Acquisition : **≥ 30 images par classe** (j'en ai pris : [__]). Variation volontaire de l'angle, de la distance, de l'éclairage et de l'arrière-plan.
3. Entraînement (*Train Model*) avec les paramètres par défaut : [époques = 50, taille de lot = 16, taux d'apprentissage = 0,001 — vérifier dans *Advanced*].
4. Test en direct : présentation de chaque objet devant la caméra, puis d'un objet inconnu.
5. Export : *Export Model → Upload* ; lien collé dans `MODEL_URL` de `code/index.html`.

## 4. Ce qui s'est passé pendant l'entraînement
> Adapter au contenu exact du « Module 11 » du cours (mes supports fournis ne contenant pas ce module, j'ai utilisé les notions générales ci-dessous).

- **Apprentissage supervisé** : chaque image est associée à une étiquette (la classe). Le modèle n'a pas de règle écrite à la main ; il **déduit les régularités** des exemples.
- **Transfert d'apprentissage** : Teachable Machine part d'un réseau de neurones convolutif **déjà entraîné** sur de grandes bases d'images
  (MobileNet) ; seule la dernière couche de classification est ré-entraînée sur mes images. C'est ce qui permet d'apprendre avec peu d'exemples et en quelques secondes.
- **Époques et perte** : à chaque époque, le modèle voit tous les exemples, compare sa prédiction à l'étiquette (**fonction de perte**) et ajuste ses poids pour réduire l'erreur. La perte diminue, la précision augmente.
- **Sortie** : pour une image, le modèle renvoie une **probabilité par classe** (somme = 100 %) ; la classe affichée est la plus probable.

## 5. Résultats
| Test | Résultat attendu | Probabilité affichée | OK ? |
|---|---|---|---|
| [Objet 1] | [Objet 1] | [__ %] | [ ] |
| [Objet 2] | [Objet 2] | [__ %] | [ ] |
| Main vide | Main vide | [__ %] | [ ] |
| Objet inconnu | ? | [__ %] | [ ] |

Captures : `captures/01_classes_et_echantillons.png`, `captures/02_entrainement.png`, `captures/03_reconnaissance_reussie.png`

## 6. Analyse critique
- **Généralisation vs sur-apprentissage** : un modèle entraîné dans un seul décor peut échouer ailleurs ; d'où la variété des prises de vue.
- **Classe « arrière-plan »** : sans elle, le modèle doit toujours choisir parmi les objets, même quand il n'y en a pas.
- **Lien avec la robotique** : la caméra est un **capteur passif extéroceptif** (le cours cite les caméras CCD/CMOS) ; le modèle réalise la
  « reconnaissance d'objet », l'une des fonctions des capteurs de vision. Embarqué sur un robot, il fournirait la perception pour décider d'une action (saisie, tri).
- **Limites** : dépend de l'éclairage ; probabilité élevée ≠ prédiction correcte (le modèle peut être « sûr de lui » sur un objet inconnu).
