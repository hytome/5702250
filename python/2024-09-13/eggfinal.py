#Version : 2024/09/13

def main():
    egg()  # 계란 도형 출력
    tea_cup()  # 찻잔 도형 출력
    stop_sign()  # STOP 표지판 출력
    hat()  # 모자 도형 출력


# 계란 도형의 윗부분을 출력하는 함수
def egg_top():
    print("  ------  ")
    print(" /      \\ ")
    print("/        \\")


# 계란 도형의 아랫부분을 출력하는 함수
def egg_bottom():
    print("\\        /")
    print(" \\______/")


# 구분선을 출력하는 함수
def line():
    print("+--------+")


# 계란 도형 전체를 출력하는 함수
def egg():
    egg_top()
    egg_bottom()
    print()


# 찻잔 도형을 출력하는 함수
def tea_cup():
    egg_bottom()
    line()
    print()


# STOP 표지판을 출력하는 함수
def stop_sign():
    egg_top()
    print("|  STOP  |")
    egg_bottom()
    print()


# 모자 도형을 출력하는 함수
def hat():
    egg_top()
    line()
    print()
    



if __name__ == "__main__":
    main()  # 프로그램 시작점