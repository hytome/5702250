def biggest_and_smallest():
    
    count = int(input("How many numbers? "))
    
    
    first_number = int(input("Next number? "))
    biggest = first_number
    smallest = first_number
    
    
    for _ in range(count - 1):
        number = int(input("Next number? "))
        if number > biggest:
            biggest = number
        if number < smallest:
            smallest = number
    

    print(f"Biggest = {biggest}")
    print(f"Smallest = {smallest}")

#
biggest_and_smallest()