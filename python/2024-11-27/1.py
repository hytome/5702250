import random

def roll_dice_until_seven():
    tries = 0
    while True:
        die1 = random.randint(1, 6)
        die2 = random.randint(1, 6)
        total = die1 + die2
        tries += 1
        print(f"{die1} + {die2} = {total}")
        if total == 7:
            print(f"You won after {tries} tries!")
            break

roll_dice_until_seven()