import random
import math

MAX_COORDINATE = 100

def main():
    print("This program is a 2-D guessing game.")
    print(f"I will think of a point somewhere\nbetween (1, 1) and ({MAX_COORDINATE}, {MAX_COORDINATE})\nand give hints until you guess it.\n")
    
    total_games = 0
    total_guesses = 0
    
    while True:
        guesses = play_one_game()
        total_games += 1
        total_guesses += guesses
        
        if not play_again():
            break
    
    print_overall_stats(total_games, total_guesses)

def play_one_game():
    x_target = random.randint(1, MAX_COORDINATE)
    y_target = random.randint(1, MAX_COORDINATE)
    guesses = 0
    
    while True:
        x_guess, y_guess = get_guess()
        guesses += 1
        if x_guess == x_target and y_guess == y_target:
            if guesses == 1:
                print(f"You got it right in 1 guess!")
            else:
                print(f"You got it right in {guesses} guesses!")
            break
        else:
            give_hint(x_guess, y_guess, x_target, y_target)
    
    return guesses

def get_guess():
    x, y = map(int, input("Guess x and y: ").split())
    return x, y

def give_hint(x_guess, y_guess, x_target, y_target):
    distance = calculate_distance(x_guess, y_guess, x_target, y_target)
    
    if distance <= 1.5:
        print("You're hot!", end=" ")
    elif distance <= 5.0:
        print("You're warm.", end=" ")
    else:
        print("You're cold.", end=" ")
    
    directions = []
    if y_guess < y_target:
        directions.append("north")
    elif y_guess > y_target:
        directions.append("south")
    
    if x_guess < x_target:
        directions.append("east")
    elif x_guess > x_target:
        directions.append("west")
    
    if directions:
        print("Go " + " ".join(directions))

def calculate_distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def play_again():
    response = input("Play again? ")
    print()
    return response.strip().lower().startswith('y')
    

def print_overall_stats(total_games, total_guesses):
    average_guesses = total_guesses / total_games if total_games > 0 else 0
    print("Overall results:")
    print(f"Games played  = {total_games}")
    print(f"Total guesses = {total_guesses}")
    print(f"Guesses/game  = {round(average_guesses, 1)}")

if __name__ == "__main__":
    main()
