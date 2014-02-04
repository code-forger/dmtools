def fix_dice(roll):
    if roll < 4:
        roll = 2
    elif roll < 6:
        roll = 4
    elif roll < 8:
        roll = 6
    elif roll < 10:
        roll = 8
    elif roll < 12:
        roll = 10
    elif roll < 20:
        roll = 12
    elif roll < 100:
        roll = 20
    else:
        roll = 100
    return roll
