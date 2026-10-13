# ---------------------------------------------------------------
# Devoir 2 - Robot évitant les obstacles (VEXcode VR, Python)
# Capteur : front_distance (distance frontale, en mm)
# Stratégie : avancer ; si obstacle < SEUIL -> stop, regarder à droite et à gauche,
#             tourner vers le côté le plus dégagé, puis repartir.
# ---------------------------------------------------------------
from vexcode_vr import *

# ----------------- PARAMÈTRES ----------------------------------
SEUIL_MM    = 250     # distance de déclenchement de l'évitement
TURN_ANGLE  = 90      # angle d'exploration (degrés)
DRIVE_SPEED = 50      # vitesse d'avance (%)
TURN_SPEED  = 40      # vitesse de rotation (%)
LOOP_MS     = 20

drivetrain.set_drive_velocity(DRIVE_SPEED, PERCENT)
drivetrain.set_turn_velocity(TURN_SPEED, PERCENT)

def distance():
    return front_distance.get_distance(MM)

def avoid():
    drivetrain.stop()
    # exploration à droite
    drivetrain.turn_for(RIGHT, TURN_ANGLE, DEGREES)
    d_right = distance()
    # exploration à gauche (rotation de 2 x l'angle pour passer de droite à gauche)
    drivetrain.turn_for(LEFT, 2 * TURN_ANGLE, DEGREES)
    d_left = distance()
    # choix du côté le plus dégagé
    if d_right > d_left:
        drivetrain.turn_for(RIGHT, 2 * TURN_ANGLE, DEGREES)
    # sinon : on reste orienté à gauche

while True:
    if distance() < SEUIL_MM:
        avoid()
    else:
        drivetrain.drive(FORWARD)
    wait(LOOP_MS, MSEC)
