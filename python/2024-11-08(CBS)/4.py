def is_prime_number(num):
    
    if num < 2:
        return False
    
    if num == 2:
        return True
    
    if num % 2 == 0:
        return False
    
    for i in range(3, int(num**0.5) + 1, 2):
        if num % i == 0:
            return False
    return True


print(is_prime_number(2))  
print(is_prime_number(4))  
print(is_prime_number(17)) 
print(is_prime_number(18)) 
