#Exercise:Name number.
#Elon
#lon
#on
#n
def print_name_variations(name):
    
    for i in range(len(name)):
        print(name[i:])
    for i in range(1, len(name) + 1):
        print(name[:i])
# 'elon'을 입력으로 사용
print_name_variations('elon')