def Box_size():
    global width_large, height_large, width_small, height_small
    width_large =  10
    height_large = 3
    width_small = 5
    height_small = 2


def draw_Big_box():
    
    print("+" + "/\\" * width_large + "+")
    draw_Big_Mid_line()
    print("+" + "/\\" * width_large + "+")

def draw_Big_Mid_line():
    for _ in range(height_large):
        print("|" + " " * (width_large * 2) + "|")


def draw_Small_box():
    print("+" + "/\\" * width_small + "+")
    draw_Small_Mid_line()
    print("+" + "/\\" * width_small + "+")

def draw_Small_Mid_line():
    for _ in range(height_small):
        print("|" + " " * (width_small * 2) + "|")
        

def main():
    Box_size()
    draw_Big_box()
    print()
    draw_Small_box()
    
main()