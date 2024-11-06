# 사용자 입력 받기
height = float(input("height (in cm)? "))
weight = float(input("weight (in kg)? "))
age = int(input("age (in years)? "))
gender = input("gender (male or female)? ").strip().lower()

# BMR 계산
if gender == "male":
    bmr = 10 * weight + 6.25 * height - 5 * age + 5
elif gender == "female":
    bmr = 10 * weight + 6.25 * height - 5 * age - 161
else:
    print("Invalid gender input")
    exit()

# 소모 수준 판별
if bmr < 1200:
    burn_level = "low resting burn rate"
elif 1200 <= bmr <= 2000:
    burn_level = "moderate resting burn rate"
else:
    burn_level = "high resting burn rate"

# 결과 출력
print(f"Person's basal metabolic rate = {int(bmr)}")
print(burn_level)
