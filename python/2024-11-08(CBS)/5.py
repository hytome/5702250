def larger_abs_val(a, b):
    # 두 값의 절대값을 비교하여 더 큰 값을 반환
    return max(abs(a), abs(b))

# 테스트 코드
print(larger_abs_val(11, 2))   # 11
print(larger_abs_val(4, -5))   # 5
print(larger_abs_val(-10, -7)) # 10