def calculate_bmi(weight, height):
    return weight / (height ** 2) * 703

def determine_bmi_class(bmi):
    if bmi < 18.5:
        return "class 1"
    elif 18.5 <= bmi < 25.0:
        return "class 2"
    elif 25.0 <= bmi < 30.0:
        return "class 3"
    else:
        return "class 4"

def main():
    print("This program reads data for two people")
    print("and computes their body mass index (BMI).")
    
    for j in range(1, 3):
        print(f"\nPerson {j} information:")
        height = float(input("height (in inches)? "))
        weight = float(input("weight (in pounds)? "))
        
        bmi = calculate_bmi(weight, height)
        bmi_class = determine_bmi_class(bmi)
        
        print(f"BMI = {bmi:.1f}")
        print(bmi_class)
    
    print("\nHave a nice day!")
    
    
main()