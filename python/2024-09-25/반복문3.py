#섭씨 온도를 화씨 온도로 변환하여 출력.
high_temp = 5
#5나누기 2의 값 2에서 +1=3.
#즉 range는 -3~3까지.
for i in range(-3, high_temp // 2 + 1):
    print(i * 1.8 + 32)