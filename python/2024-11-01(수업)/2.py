def print_name_border(full_name):
    # 대문자로 변환 후 공백을 기준으로 분리
    parts = full_name.upper().split()
    
    # 이름과 성을 분리
    first_name = parts[0]
    last_name = ''.join(parts[1:])  # 나머지를 성으로 처리
    
    # 첫 번째 이름 변형 출력
    for i in range(len(first_name)):
        print(first_name[i:])
    
    # 첫 번째 이름 변형 출력 (역순)
    for i in range(1, len(first_name) + 1):
        print(first_name[:i])
    
    # 두 번째 이름 변형 출력
    for i in range(len(last_name)):
        print(last_name[i:])
    
    # 두 번째 이름 변형 출력 (역순)
    for i in range(1, len(last_name) + 1):
        print(last_name[:i])

# 사용자로부터 전체 이름을 입력받음
user_input = input("이름과 성을 공백으로 구분하여 입력하세요: ")
print_name_border(user_input)