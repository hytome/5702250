def main():
    world()
    turtle_equal()
    turtle_v()

def world():
    print("  .-'';'-.")
    print(" .'  <_,-'.")
    print("/ ) ,--.>\\ \\")
    print("|' (    \\_ |")
    print("|  | .-.  |")
    print("\\  '-' ;_/")
    print(" '._\\_,'('")
    print("   '._/_,\"")
    print("     `---'")

def turtle_equal():
    print("   ____   _")
    for i in range(1, 3):
        print(" " * (3 - i) + "/" + "= " * (i + 1) + "\\"+ "\\" + "/\\" )
    print(" ou ou")

def turtle_v():
    print("   ____   _")
    for i in range(1, 3):
         print(" " * (3 - i) + "/" + "v " * (i + 1) + "\\"+ "\\" + "/\\")
    print(" ou ou")

main()
