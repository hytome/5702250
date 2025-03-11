using Ststem;

namespace project0307 {
    class Program {

        static void Main(string[] args) {
            //디스플레이 변수 이어서 공부...
            string firstName = "heo ";
            string lastName = "hyun";
            string fullName = firstName + lastName;
            Console.WriteLine(fullName);
            int x = 5;
            int y = 10;
            Console.WriteLine(x + y);
            //많은 변수 선언하기.
            int x = 5, y = 6, z = 7;
            Console.WriteLine(x + y + z);
            //여러 변수에 동일한 값도 가능하다.
            int a , b , c;
            a = b = c = 10;
            Console.WriteLine(a + b + c);
        }
    }
}