def average_of_2(num1, num2):
    """
    두 정수의 평균을 계산하는 함수
    매개변수:
        num1 (int): 첫 번째 정수
        num2 (int): 두 번째 정수
    반환값:
        float: 두 정수의 평균값
    """
    # 두 수를 더한 후 2로 나누어 평균 계산
    return (num1 + num2) / 2

# 테스트
print(average_of_2(2, 9))  # 예상 출력: 5.5
