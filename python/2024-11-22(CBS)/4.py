def gpa_message(gpa):
    credits = gpa * 3
    
    if abs(credits - 9.6) <= 0.1:
        print("You earned the correct amount of credits!")
    else:
        print("Incorrect credits.")