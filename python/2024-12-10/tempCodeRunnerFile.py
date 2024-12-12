import random
import math

# 상수 선언 (X, Y 좌표의 최대 값)
MAX_COORDINATE = 100  # 변경 사항: 20 -> 100

def main():
    print("This program is a 2-D guessing game.")
    print(f"I will think of a point\nsomewhere between (1, 1) and ({MAX_COORDINATE}, {MAX_COORDINATE})\n and give hints until you guess it.")
    
    total_games = 0
    total_guesses = 0
    best_game_guesses = float('inf')
    
    while True:
        guesses = play_one_game()
        total_games += 1
        total_guesses += guesses
        best_game_guesses = min(best_game_guesses, guesses)
        
        if not play_again():
            break
    
    print_overall_stats(total_games, total_guesses, best_game_guesses)

def play_one_game():
    """한 게임을 실행하고, 총 추측 횟수를 반환합니다."""
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
    """사용자로부터 x, y 좌표를 입력받아 반환합니다."""
    x, y = map(int, input("Guess x and y: ").split())
    return x, y

def give_hint(x_guess, y_guess, x_target, y_target):
    """현재 추측에 대해 힌트를 제공합니다 (hot, warm, cold, 방향 등)."""
    distance = calculate_distance(x_guess, y_guess, x_target, y_target)
    
    if distance <= 1.5:
        print("You're hot!", end=" ")
    elif distance <= 5.0:
        print("You're warm.", end=" ")
    else:
        print("You're cold.", end=" ")
    
    if y_guess < y_target:
        print("Go north", end=" ")
    elif y_guess > y_target:
        print("Go south", end=" ")
    
    if x_guess < x_target:
        print("Go east")  # 변경 사항: "Go" 추가
    elif x_guess > x_target:
        print("Go west")  # 변경 사항: "Go" 추가
    else:
        print()

def calculate_distance(x1, y1, x2, y2):
    """두 점 (x1, y1)과 (x2, y2) 사이의 거리를 계산합니다."""
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def play_again():
    """사용자에게 다시 플레이할 것인지 묻고, 'y'로 시작하는 대답에 대해 True를 반환합니다."""
    response = input("Play again? ").strip().lower()
    return response.startswith('y')

def print_overall_stats(total_games, total_guesses, best_game_guesses):
    """전체 통계를 출력합니다."""
    average_guesses = total_guesses / total_games if total_games > 0 else 0
    print("\nOverall results:")
    print(f"Games played  = {total_games}")
    print(f"Total guesses = {total_guesses}")
    print(f"Guesses/game  = {round(average_guesses, 1)}")
    print(f"Best game     = {best_game_guesses}")  # 변경 사항: Best game 출력 추가

# 프로그램 실행
if __name__ == "__main__":
    main()
