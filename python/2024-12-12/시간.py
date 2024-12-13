def hours():
    """
    직원들의 근무 시간 데이터를 읽고 분석하는 함수
    - 각 직원의 총 근무 시간과 일평균 근무 시간을 계산
    - 결과를 지정된 형식으로 출력
    """
    # 파일명 입력 받기
    filename = input("Input file? ")
    
    # 파일 읽기
    with open(filename, 'r') as file:
        # 각 줄(직원) 처리
        for line in file:
            # 공백으로 데이터 분리
            data = line.split()
            
            # 기본 정보 추출
            id_num = data[0]        # 직원 ID
            name = data[1]          # 직원 이름
            hours_list = data[2:]   # 일별 근무 시간 리스트
            
            # 근무 시간 계산
            total_hours = 0.0       # 총 근무 시간
            for hour in hours_list:
                total_hours += float(hour)
            
            # 일평균 근무 시간 계산
            days = len(hours_list)  # 근무 일수
            avg_hours = total_hours / days
            
            # 결과 출력 (소수점 첫째 자리까지 표시)
            print(f"{name} (ID#{id_num}) worked {total_hours:.1f} hours ({avg_hours:.1f}/day)")

# 프로그램 실행
if __name__ == "__main__":
    hours()
