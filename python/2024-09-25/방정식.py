#루프를 사용하여 특정 패턴 의 숫자를 출력
# 카운트가 1에서 5까지 증가하면서 각count에 대해 5*count-3을 계산하여 출력.
for count in range(1, 6):
    number_to_print = 5 * count - 3
    print(number_to_print)

print()    

for size in range(1,6):
    number_of_size = -4 * size + 21
    print(number_of_size)