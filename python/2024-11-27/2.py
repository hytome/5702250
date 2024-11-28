import random

def adding_game():
    points = 0
    incorrect_attempts = 0

    while incorrect_attempts < 3:
        num_count = random.randint(2, 5)
        numbers = [random.randint(1, 10) for _ in range(num_count)]
        correct_answer = sum(numbers)

        question = " + ".join(map(str, numbers))
        user_answer = input(f"{question} = ")

        try:
            if int(user_answer) == correct_answer:
                points += 1
                print("Correct!")
            else:
                incorrect_attempts += 1
                print(f"Wrong! The answer was {correct_answer}")
        except ValueError:
            incorrect_attempts += 1
            print(f"Wrong! The answer was {correct_answer}")

    print(f"You earned {points} total points")

adding_game()