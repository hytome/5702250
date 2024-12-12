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
                print("정답입니다!")
            else:
                incorrect_attempts += 1
                print(f"틀렸습니다! 정답은 {correct_answer}입니다.")
        except ValueError:
            incorrect_attempts += 1
            print(f"틀렸습니다! 정답은 {correct_answer}입니다.")

    print(f"총 {points}점을 획득하셨습니다.")

adding_game()