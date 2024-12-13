def coin_flip(filename):
    """
    파일에서 동전 던지기 결과를 읽고 분석하는 함수
    매개변수:
        filename (str): 입력 파일의 이름
    동작:
        - 파일에서 동전 던지기 결과(H/T 또는 Heads/Tails)를 읽음
        - 앞면(H/Heads)의 개수와 비율을 계산
        - 50% 이상이면 승리, 미만이면 패배 메시지 출력
    """
    # 결과를 저장할 변수 초기화
    heads_count = 0    # 앞면이 나온 횟수
    total_flips = 0    # 전체 동전 던지기 횟수
    
    # 파일을 열어서 내용을 읽음
    with open(filename, 'r') as file:
        # 파일의 각 줄을 처리
        for line in file:
            # 공백을 기준으로 각 토큰(단어)으로 분리
            # 예: "H T Heads" -> ["H", "T", "Heads"]
            tokens = line.split()
            
            # 각 토큰을 순회하면서 처리
            for token in tokens:
                # 대소문자 구분 없이 처리하기 위해 소문자로 변환
                # 예: "Heads" -> "heads", "H" -> "h"
                token = token.lower()
                total_flips += 1    # 전체 던지기 횟수 증가
                
                # 현재 토큰이 앞면인 경우 카운트 증가
                # 'h' 또는 'heads'인 경우를 앞면으로 간주
                if token == 'h' or token == 'heads':
                    heads_count += 1
    
    # 앞면이 나온 비율을 백분율로 계산
    # 소수점 첫째 자리까지 표시하기 위해 반올림하지 않음
    percentage = (heads_count / total_flips) * 100
    
    # 결과 출력 (앞면 개수와 비율)
    # .1f 형식 지정자를 사용하여 소수점 첫째 자리까지 표시
    print(f"{heads_count} heads ({percentage:.1f}%)")
    
    # 승패 판정 및 결과 메시지 출력
    # 50% 이상인 경우 승리, 미만인 경우 패배
    if percentage >= 50:
        print("You win!")    # 승리 메시지
    else:
        print("You lose!")   # 패배 메시지

# 프로그램의 시작점
if __name__ == "__main__":
    coin_flip("flips.txt")   # 테스트를 위한 파일명