def input_stats(filename):
    """
    파일의 각 줄에 대한 통계를 계산하고 출력하는 함수
    매개변수:
        filename (str): 분석할 파일의 이름
    """
    try:
        # 통계 변수 초기화
        line_count = 0      # 총 줄 수
        total_chars = 0     # 전체 문자 수
        longest_line = 0    # 가장 긴 줄의 길이
        
        # 파일 읽기
        with open(filename, 'r') as file:
            # 각 줄 처리
            for line in file:
                line_count += 1
                # 줄바꿈 문자를 제외한 실제 문자 수
                chars = len(line.rstrip('\n'))
                
                # 통계 업데이트
                total_chars += chars
                longest_line = max(longest_line, chars)
                
                # 현재 줄의 정보 출력
                print(f"Line {line_count} has {chars} chars")
            
            # 평균 계산 (소수점 첫째 자리까지)
            average = total_chars / line_count
            
            # 최종 통계 출력
            print(f"{line_count} lines longest = {longest_line}, average = {average:.1f}")
            
    except FileNotFoundError:
        # 파일이 존재하지 않는 경우 아무것도 출력하지 않음
        return

# 테스트
if __name__ == "__main__":
    input_stats("carroll.txt")