import math

# 수학 표현식 평가
result1 = abs(-1.23)
result2 = math.sqrt(121.0) - math.sqrt(256.0)
pi = 3.141592653589793
e = 2.718281828459045
result3 = round(pi) + round(e)
result4 = math.ceil(6.022) + math.floor(15.9994)
result5 = abs(min(-3, -5))

# 결과 출력
print("abs(-1.23):", result1)
print("math.sqrt(121.0) - math.sqrt(256.0):", result2)
print("round(pi) + round(e):", result3)
print("math.ceil(6.022) + math.floor(15.9994):", result4)
print("abs(min(-3, -5)):", result5)

# age 변수 처리
age = -5  # 예시 값

# 음수를 0으로 대체
age = max(0, age)

# 최대 나이를 40으로 제한
age = min(40, age)

print("Processed age:", age)