namespace project0311
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //사용자 입력받기. 이제 는 출력이 아니라 입력을 구현해보자에요.
            Console.WriteLine("Enter Your Name: ");
            String? username = Console.ReadLine();
            //ReadLine: 이것이 바로 c언어의 scanf같은것 string? 뒤에 ?가 붙으면 null도 허용한다는것.
            //즉 ReadLine에서 내가 입력한 문자열 값을 username에 저장해라. 
            Console.WriteLine("User name is: " + username);


            //그러나 이 ReadLine은 string. 메서드를 반환하기 때문에 int로 선언시 오류가 발생합니다.
            //이것을 해결하는 방법. 저번에 배운 형 병환을 응용해보자.
            Console.WriteLine("Enter Your age:");
            int myage = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Your age is " +  myage);
            // 다음 쳅터: 연산자. 연산자는 변수의 값에 대한 연상을 수행하는데 사용된다.

            int x = 100 + 50;
            //또현 변수와 다른 변수를 더한다고 사용할 수 있습니다. 
            int y = x + 250; //이렇게 x의 150 결과값과 250을 더할수 있다.
            int z = x + y; // 이런식으로도 변수와 변수 결과 값도 가능.
            // 산술연산자 /= 나눗셈 %= 나머지를 반환. 

            //다음은 할당 연산자.:할당 연산자는 변수에 값을 할당하는데 사용된다.
            int num1 = 10;  //이렇게 num1에 10이라는 값을 할당할수도 있고.
            num1 += 5; //이런 방식으로 5의 값을 추가할수도 있다. 
            // &:and ^:xor. >>= 오른쪽으로 비트이동. <<= 왼쪽으로 비트이동.


            Console.WriteLine("Hello, World!");
        }
    }
}
