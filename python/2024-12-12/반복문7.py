def cal_bmi(weight, height):
    return weight / (height **2) * 703

def get_bmi_category(bmi):
    if bmi < 18.5:
        return "class1"
    elif 18.5 <= bmi < 25.0:
        return "class2"
    elif 25.0 <= bmi < 30.0:
        return "class3"
    else:
        return "class4"
    

def main():
    print("This program reads data for two people")
    print("and computers their boday mass index (BMI)")

    for j in range (1,3):
        print(f"\nPerson {j} information ")
        height = float(input("height(in inches)" ))
        weight = float(input("weight(in pounds)"))
        bmi = cal_bmi(weight, height)
        category = get_bmi_category(bmi)
        print(f"BMI :{bmi:.1f}")
        print(f"category: {category}")

if __name__ == "__main__":
    main()
