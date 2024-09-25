def print_complex_figure(height):
    # 윗부분 테두리 출력.
    print("+" + "-" * (2 * height) + "+")
    #+를 양끝에 내가 2*height내가 선언한 값이 4니까 4곱하기 2가 된다. 
    
    for line in range(1, height + 2):
        #1부터 height+2 까지. 내가 입력한 값은 4니까  1~6번 반복하는것.
        spaces = line - 1
        #처음 값은 1이니 공백은 0. 그다음은 1..이렇게 공백을 늘려가는 용도.
        print("|" + " " * spaces + "\\", end="")
        #도형의 왼쪽 부분을 담당할 출력문. 공백이 점점 " "*space로 늘릴 수 있다. 
        
        # 숫자 출력
        num_count = 2 * (height - spaces)
        #num_count변수는 현재 줄에서 출력할 숫자의 갯수를 결정한다.
        #처음은 2*(line-1)spaces=0 height=4이니 8이 된다.
        for num in range(1, num_count + 1):
            #반복문으로 숫자를 출력한다.1~8까지 출력하기 위하여 즉 8번  반복하기 위하여 +1.
            print(num, end="")
            #숫자를 출력하고 공백.
        
        print("/" + " " * spaces + "|")
        #도형의 오른쪽 부분을 담당한다.
    
    # 아랫부분 테두리
    print("+" + "-" * (2 * height) + "+")

# 도형 출력
print_complex_figure(4)