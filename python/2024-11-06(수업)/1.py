def main():
    print("Enter person's information:")
    height = int(input("height (in cm)? "))
    weight = int(input("weight (in kg)? "))
    age  = int(input("age (in years)?"))
    gender = input("gender (male or female)?")
    
    if gender == "male":
        bmr = 10 * weight + 6.25 * height - 5 * age + 5
    elif gender == "female":
        bmr = 10 * weight + 6.25 * height - 5 * age - 161
    else:
        print("Invalid gender input")
        exit()
        
    if bmr < 1200:
        burn_level = "low resting burn rate"
    elif 1200 <= bmr <= 2000:
        burn_level = "moderate resting burn rate"
    else:
        burn_level = "high resting burn rate"


    print(f"Person's basal metabolic rate = {int(bmr)}")
    print(burn_level)
        