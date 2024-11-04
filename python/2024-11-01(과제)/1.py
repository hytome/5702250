def box_of_stars(width, height):
    
    print("*" * width)
    
    
    for _ in range(height - 2):
        print("*" + " " * (width - 2) + "*")
    
    
    print("*" * width)


box_of_stars(8, 5)
