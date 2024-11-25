def days_in_month(month):

    days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    
    
    if 1 <= month <= 12:
        return days[month - 1]
    else:
        return "Invalid month"  