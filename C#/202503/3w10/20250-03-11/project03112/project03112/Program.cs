using System.Security.Cryptography.X509Certificates;

namespace project03112
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //다음에 공부할것은 비교연산자입니다. 두값이나 변수를 비교하는데 사용.
            int x = 5;
            int y = 3;
            Console.Write(x > y);
            //5는 3보다 크니까 true를 반환 합니다.
            //논리연산자. &&: 둘다 조건일치 ||:둘중 하나라도 조건일치. !=둘다 조건 불일치.
            //c# 수학.
            Math.Max(5, 10); //5와 10 중에서 더 큰 값을 찾는 함수.
            Math.Min(5, 10); //5와 10 중에서 더 작은 값을 찾는 함수.
            Math.Sqrt(64); //제곱근 root를 구하는 함수. 64의 제곱근 8을 반환.
            Math.Abs(-4.7); //절대값을 반환 하는 함수.
            Math.Round(9.99); //가장 가까운 정수로 반올림을 하는 기능.  결과:10.
            //C#문자열. 
            //string은 따옴표를 이용하여 변수 값을 할당한다. 
            string greeting = "Hello";
            string greeting2 = "nice to meet you!";
            string txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            Console.WriteLine("The legth of the txt string is: " + txt.Length);
            //Length:텍스트,문자열의 길이를 반환하는 기능. 

            Console.WriteLine(greeting);
            Console.WriteLine(greeting2);

            //다른방법. To를 이용하여 대문자로 소문자로 변환하는법.
            string txt2 = "YEAH";
            Console.WriteLine(txt2.ToLower());
            Console.WriteLine(txt2.ToUpper());
            //C# 문자열 연결.
            string firname = "HEO ";
            //연결을 위해 공백 유지.
            string lasname = "HYUN";
            string myname = firname + lasname;
            //이런식으로 문자열 연결도 가능하다에요.

            Console.WriteLine(myname);

            //다른 방법. string.Concat();
            string caname = string.Concat(firname, lasname);
            Console.WriteLine(caname);
            //대신 문자열이 아니고 정수형태에 +를 쓰면 그냥 합으로 저장된다는걸 떠올리자.





            Console.WriteLine("Hello, World!");
        }
    }
}
