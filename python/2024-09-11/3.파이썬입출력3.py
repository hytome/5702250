def print_hello():
        print("hello")
print_hello()
def message1():
         print("This is message1")
def message2():
         print("this is message2")
         message1()
         print("done message2.")

message1()
message2()
print("Done with everything")

#def:파이썬에서 함수를 정의할떄 사용하는 키워드.
#여기서는 print_hello는 "hello"를 출력 하는 기능을 한다.