def main():
    num = int(input())
    for i in range(1, num + 1):
        num1, num2 = map(int, input().split())
        result = num1 + num2
        print(result)

if __name__ == "__main__":
    main()