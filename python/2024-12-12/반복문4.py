def binary_to_decimal(binary):
    """
    2진수를 10진수로 변환하는 함수
    매개변수:
        binary (int): 2진수 형태의 정수
    반환값:
        int: 변환된 10진수 값
    """
    decimal = 0  # 최종 10진수 결과를 저장할 변수
    power = 0    # 2의 거듭제곱 지수 즉 2의 몇승인지.
    
    # binary가 0이 될 때까지 반복
    while binary > 0:
        # 현재 자릿수(0 또는 1) 추출
        digit = binary % 10
        # 현재 자릿수에 2의 거듭제곱을 곱하여 더함
        decimal += digit * (2 ** power)
        # 다음 자릿수로 이동
        binary //= 10
        #10의 자리수 제거. 이래야 다음 자리수를 추출하고 또 반복문이 이어감.
        power += 1
        # 다음 거듭제곱 
    return decimal                    

# 테스트
print(binary_to_decimal(101011))  # 예상 출력: 43
