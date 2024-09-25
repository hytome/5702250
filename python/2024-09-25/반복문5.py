# 큰 사각형 출력
width_large = 10
height_large = 3

# 윗변과 아랫변
print("+" + "/\\" * width_large + "+")
for _ in range(height_large):
    print("|" + " " * (width_large * 2) + "|")
print("+" + "/\\" * width_large + "+")

print()  # 도형 사이에 빈 줄 추가

# 작은 사각형 출력
width_small = 5
height_small = 2

# 윗변과 아랫변
print("+" + "/\\" * width_small + "+")
for _ in range(height_small):
    print("|" + " " * (width_small * 2) + "|")
print("+" + "/\\" * width_small + "+")