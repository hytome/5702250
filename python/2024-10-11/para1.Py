def write_on_board(times):
    for i in range(0, times):
        print("I will not sleep through my education")

def main():
    # 사용자로부터 입력 받기
    times = int(input("몇 번 출력하시겠습니까? "))
    write_on_board(times)

if __name__ == "__main__":
    main()