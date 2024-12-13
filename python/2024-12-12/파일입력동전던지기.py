def coin_flip(filename):
    """
    파일에서 동전 던지기 결과를 읽고 분석하는 함수
    매개변수:
        filename (str): 입력 파일의 이름
    """
    # 앞면(heads) 카운트와 전체 동전 던지기 횟수
    heads_count = 0
    total_flips = 0
    
    # 파일 읽기
    with open(filename, 'r') as file:
        # 파일의 모든 내용을 읽어서 처리
        for line in file:
            # 각 토큰을 공백으로 분리
            tokens = line.split()
            
            # 각 토큰 처리
            for token in tokens:
                token = token.lower()  # 대소문자 구분 없이 처리
                total_flips += 1
                
                # 앞면(H 또는 heads)인 경우 카운트 증가
                if token == 'h' or token == 'heads':
                    heads_count += 1
    
    # 앞면이 나온 비율 계산 (반올림)
    percentage = round((heads_count / total_flips) * 100)
    
    # 결과 출력
    print(f"{heads_count} heads ({percentage}%)")
    
    # 승패 결정 (50% 이상이면 승리)
    if percentage >= 50:
        print("You win!")
    else:
        print("You lose!")

# 테스트
if __name__ == "__main__":
    coin_flip("flips.txt") 