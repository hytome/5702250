def box_of_stars(width, height):
    print("*" * width)
    for i in range(height -2):
        print ("*" + " "*(width - 2)+ "*")

    print("*" * width)


box_of_stars(10, 5)