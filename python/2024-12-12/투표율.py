def election():
    """
    선거 결과 파일을 읽어서 각 후보자의 선거인단 투표 수를 계산하는 함수
    """
    # 파일명 입력 받기
    filename = input("Input file? ")
    
    # 각 후보자의 선거인단 투표 수를 저장할 변수
    candidate1_votes = 0
    candidate2_votes = 0
    
    # 파일 읽기
    with open(filename, 'r') as file:
        for line in file:
            # 공백을 기준으로 데이터 분리
            data = line.split()
            
            # 필요한 데이터 추출
            candidate1_percent = float(data[1])  # 후보자1 득표율
            candidate2_percent = float(data[2])  # 후보자2 득표율
            electoral_votes = int(data[3])       # 선거인단 수
            
            # 승자 결정 및 선거인단 투표 할당
            if candidate1_percent == candidate2_percent:
                continue  # 동률인 경우 아무에게도 표를 주지 않음
            elif candidate1_percent > candidate2_percent:
                candidate1_votes += electoral_votes
            else:
                candidate2_votes += electoral_votes
    
    # 결과 출력
    print(f"Candidate 1: {candidate1_votes} votes")
    print(f"Candidate 2: {candidate2_votes} votes")

# 프로그램 실행
if __name__ == "__main__":
    election()
