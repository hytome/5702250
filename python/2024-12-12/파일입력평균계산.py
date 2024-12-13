def average_value_in_file(filename):
    total_sum = 0 #파일에 있는 모든 숫자 합계.
    count = 0 #파일에 있는 숫자 개수.

    try:
        with open(filename, 'r') as file:
            for line in file:
                    total_sum += float(line.strip())
                    count +=1

    except FileNotFoundError:
         print(f"파일{filename}을 찾을수 없다에요")
         return 0.0
    except ValueError:
         print(f"파일{filename}에 숫자가 아닌 값이 존재합니다.")
         return 0.0
    
    return total_sum/count

filename = 'data.txt'
average = average_value_in_file(filename)
print(f"{filename}의 평균값은 {average:.2f}입니다.")
