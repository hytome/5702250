def check_dates(filename):
    try:
        with open(filename, 'r') as file:
            for line in file:
                m1, d1, m2, d2 = map(int, line.split())
                date1 = f"{m1}/{d1}"
                date2 = f"{m2}/{d2}"
                
                if m1 <= m2:
                    month_diff = m2 - m1
                    
                    if month_diff == 0:
                        print(f"{date1}와(과) {date2}는 한 달 이내의 차이입니다.")
                    
                    elif month_diff == 1:
                        if d2 < d1:
                            print(f"{date1}와(과) {date2}는 한 달 이내의 차이입니다.")
                        else:
                            print(f"{date1}와(과) {date2}는 한 달 이상의 차이가 납니다!")
                    else:
                        print(f"{date1}와(과) {date2}는 한 달 이상의 차이가 납니다!")
                else:
                    if m1 == 12 and m2 == 1:
                        if d1 >= d2:
                            print(f"{date1}와(과) {date2}는 한 달 이내의 차이입니다.")
                        else:
                            print(f"{date1}와(과) {date2}는 한 달 이상의 차이가 납니다!")
                    else:
                        month_diff = m1 - m2
                        if month_diff == 1:
                            if d1 < d2:
                                print(f"{date1}와(과) {date2}는 한 달 이내의 차이입니다.")
                            else:
                                print(f"{date1}와(과) {date2}는 한 달 이상의 차이가 납니다!")
                        else:
                            print(f"{date1}와(과) {date2}는 한 달 이상의 차이가 납니다!")
                    
    except FileNotFoundError:
        pass
