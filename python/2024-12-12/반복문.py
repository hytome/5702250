import math  # 파이(π) 값을 사용하기 위한 math 모듈 임포트

def area(radius):
    """
    원의 반지름을 입력받아 면적을 계산하는 함수
    매개변수:
        radius (float): 원의 반지름 (양수)
    반환값:
        float: 원의 면적
    """
    # 원의 면적 공식: π * r²
    return math.pi * radius ** 2

# 테스트
print(area(2.0))  # 예상 출력: 12.566370614359172
