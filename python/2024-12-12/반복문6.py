def get_days_in_month(month):
    """
    주어진 월(month)에 해당하는 최대 일수를 반환하는 함수
    매개변수:
        month (int): 1월(1) ~ 12월(12) 중 하나의 월
    반환값:
        int: 해당 월의 최대 일수 (예: 1월 → 31일, 2월 → 28일 등)
    """
    # 월별 최대 일수를 담은 배열 (0번 인덱스는 사용하지 않음)
    day_in_month = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    # 주어진 월에 해당하는 최대 일수를 반환
    return day_in_month[month]


def get_absolte_day(month, day):
    """
    특정 월/일에 해당하는 날짜가 1년 중 몇 번째 날인지 계산하는 함수
    매개변수:
        month (int): 1월(1) ~ 12월(12) 중 하나의 월
        day (int): 해당 월의 일(1 ~ 31)
    반환값:
        int: 1년 중 몇 번째 날인지를 반환 (예: 1월 1일 = 1, 2월 1일 = 32 등)
    """
    total_days = day  # 현재 월의 날짜(day)부터 시작
    # 1월부터 (month - 1)월까지의 모든 일수를 누적
    for i in range(1, month):
        total_days += get_days_in_month(i)  # 이전 월들의 일수를 누적
    return total_days  # 누적된 총 일수를 반환


def days_until_birthday(today_month, today_day, birth_month, birth_day):
    """
    오늘 날짜로부터 다음 생일까지 남은 일수를 계산하는 함수
    매개변수:
        today_month (int): 오늘의 월 (1 ~ 12)
        today_day (int): 오늘의 일 (1 ~ 31)
        birth_month (int): 생일의 월 (1 ~ 12)
        birth_day (int): 생일의 일 (1 ~ 31)
    반환값:
        int: 오늘부터 다음 생일까지 남은 일수 (0이면 오늘이 생일, 1이면 내일이 생일 등)
    """
    # 오늘 날짜와 생일 날짜를 1년 중 몇 번째 날인지로 변환
    today_absolute = get_absolte_day(today_month, today_day)
    birth_absolute = get_absolte_day(birth_month, birth_day)

    if birth_absolute < today_absolute:
        # 생일이 이미 지난 경우 → 내년 생일까지의 남은 일수를 계산
        return 365 - today_absolute + birth_absolute
    else:
        # 생일이 오늘 이후인 경우 → 생일까지 남은 일수 계산
        return birth_absolute - today_absolute


def get_vaild_day_input(month):
    """
    사용자로부터 특정 월에 유효한 일(day) 입력을 받는 함수
    매개변수:
        month (int): 1월(1) ~ 12월(12) 중 하나의 월
    반환값:
        int: 사용자가 입력한 유효한 일(day)
    동작:
        - 주어진 월의 최대 일수를 구하고, 그 범위 내의 유효한 입력만 허용
        - 사용자가 올바른 값을 입력할 때까지 반복
    """
    max_days = get_days_in_month(month)  # 해당 월의 최대 일수를 가져옴
    while True:
        try:
            day = int(input(f"What is the day   (1-{max_days})? "))  # 사용자 입력
            if 1 <= day <= max_days:  # 유효한 입력인지 검사
                return day  # 유효한 경우, 입력된 값을 반환
            else:
                print(f"Please enter a valid day between 1 and {max_days}.")
        except ValueError:
            # 입력값이 정수가 아니면 오류 메시지를 출력
            print("Please enter a valid integer.")


def main():
    """
    프로그램의 메인 함수 (프로그램 실행의 시작점)
    동작:
        - 오늘의 날짜와 생일을 입력받음
        - 오늘의 날짜와 생일이 1년 중 몇 번째 날인지 계산
        - 오늘부터 생일까지 남은 일수를 계산하여 출력
        - 생일이 오늘, 내일인 경우 특별 메시지를 출력
    """
    print("This program tells you how many days")
    print("it will be until your next birthday.\n")

    # 오늘 날짜 입력
    print("Please enter today's date:")
    today_month = int(input("What is the month (1-12)? "))  # 오늘의 월 입력 (1 ~ 12)
    today_day = get_vaild_day_input(today_month)  # 오늘의 일 입력 (1 ~ 월별 최대 일수)
    today_absolute = get_absolte_day(today_month, today_day)  # 오늘이 1년 중 몇 번째 날인지 계산
    print(f"{today_month}/{today_day} is day #{today_absolute} of 365.\n")

    # 생일 입력
    print("Please enter your birthday: ")
    birth_month = int(input("What is the month (1-12)? "))  # 생일의 월 입력 (1 ~ 12)
    birth_day = get_vaild_day_input(birth_month)  # 생일의 일 입력 (1 ~ 월별 최대 일수)
    birth_absolute = get_absolte_day(birth_month, birth_day)  # 생일이 1년 중 몇 번째 날인지 계산
    print(f"{birth_month}/{birth_day} is day #{birth_absolute} of 365.\n")

    # 생일까지 남은 일수 계산
    days_left = days_until_birthday(today_month, today_day, birth_month, birth_day)

    # 결과 출력
    if days_left == 0:
        print("Happy birthday!")  # 오늘이 생일인 경우
    elif days_left == 1:
        print("Wow, your birthday is tomorrow!")  # 생일이 내일인 경우
    else:
        print(f"Your next birthday is in {days_left} days.")  # 생일까지 남은 일수가 2일 이상인 경우


# 프로그램의 시작점
main()
