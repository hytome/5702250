def decimal_to_binary(decimal):
    #10진수를 2진수로 변환하는 기능
    if decimal == 0:
        return "0" 
    #0이 넘어온 경우 2진수도 0이니까 그냥 0을 반환.
    binary = "" #2진수 를 결과를 저장할 문자열.

    while decimal >0:
        remainder  = decimal % 2
        #2나누기를 하고 나머지 값 반환.
        binary = str(remainder) + binary
        #그 나머지 값을 문자열로 점점 합치는 과정.
        decimal //= 2 #10의 자리수 제거. 이래야 다음 자리수를 추출하고 또 반복문이 이어감.
        #즉 몫을 저장하는 과정.
    return binary 

print(decimal_to_binary(43))