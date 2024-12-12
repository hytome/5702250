import random  # 랜덤 모듈 임포트

def coin_flip(k, side):
    if k <= 0 or side not in ["H", "T"]:
        print("ERROR!")
        return 

    c_count = 0  # 연속 횟수를 저장하는 변수
    flips = []  # 던지기 결과를 저장할 리스트
    
    while c_count < k:
        current_flip = 'H' if random.randint(0, 1) == 0 else 'T'
        flips.append(current_flip)
        
        if current_flip == side:
            c_count += 1
        else:
            c_count = 0
    
    print(" ".join(flips))  # 모든 던지기 결과를 공백으로 구분하여 출력
    print(f"You got {side} {k} times in a row!")  # 축하 메시지


# 프로그램의 시작 지점
if __name__ == "__main__":
    coin_flip(4, "T")
