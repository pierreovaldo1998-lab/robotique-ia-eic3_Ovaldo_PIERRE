# ---------------------------------------------------------------
# Devoir 1 - Robot suiveur de ligne (VEXcode VR, Python)
# Principe : suivi de BORD de ligne avec un correcteur proportionnel (P).
# Capteur : down_eye (capteur oeil orienté vers le sol) -> luminosité 0..100 %
# Actionneurs : left_motor, right_motor (commande différentielle)
# ---------------------------------------------------------------
from vexcode_vr import *

# ----------------- PARAMÈTRES (à calibrer, voir README) --------
BRIGHT_LINE  = 5      # luminosité mesurée sur la ligne (sombre)  -> à relever
BRIGHT_FLOOR = 90     # luminosité mesurée sur le sol (clair)     -> à relever
BASE_SPEED   = 40     # vitesse de croisière (%)
KP           = 0.45   # gain proportionnel (% de vitesse par % d'erreur)
MAX_SPEED    = 80     # saturation des moteurs (%)
LOOP_MS      = 20     # période de la boucle (ms)

TARGET = (BRIGHT_LINE + BRIGHT_FLOOR) / 2   # consigne : le bord de la ligne

def clamp(v, lo, hi):
    return max(lo, min(hi, v))

left_motor.set_velocity(BASE_SPEED, PERCENT)
right_motor.set_velocity(BASE_SPEED, PERCENT)
left_motor.spin(FORWARD)
right_motor.spin(FORWARD)

while True:
    measure = down_eye.brightness()          # mesure
    error   = TARGET - measure               # erreur = consigne - mesure
    correction = KP * error                  # loi de commande P

    # Si le robot dérive du mauvais côté, inverser le signe de 'correction'.
    left_speed  = clamp(BASE_SPEED + correction, -MAX_SPEED, MAX_SPEED)
    right_speed = clamp(BASE_SPEED - correction, -MAX_SPEED, MAX_SPEED)

    left_motor.set_velocity(left_speed, PERCENT)
    right_motor.set_velocity(right_speed, PERCENT)

    wait(LOOP_MS, MSEC)
