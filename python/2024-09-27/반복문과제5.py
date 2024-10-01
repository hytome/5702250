for row in range(1, 4):
    for i in range(row):
        print("#", end=" ")
    for i in range(4 - row):
        print("$", end=" ")
    print()  # 줄 바꿈 추가