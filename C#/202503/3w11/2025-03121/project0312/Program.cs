using System;

namespace Project0312
{
    class Program
    {
        static void Main(string[] args)
        {
            //c#부울: 참(true), 거짓(false) 켜기/끄기 예/아니오 기타등등...
            bool isCsharpFun = true;
            bool isFishTasty = false; 
            Console.WriteLine(isCsharpFun);
            Console.WriteLine(isFishTasty);
            //부울 표현식. 도 한번 해보자구.
            int x = 10;
            int y = 9;
            Console.WriteLine(x > y); //x가 y보다 크니? 참이면 true, 거짓이면 false.
            //실생활 예시.
            int myage = 25;
            int voteage = 19;
            Console.WriteLine(myage >= voteage); //내 나이가 투표 가능 나이보다 크거나 같니? 참이면 true, 거짓이면 false.
            if (myage >= voteage)
            {
                Console.WriteLine("당신은 투표가능합니다.");
            }
            else
            {
                Console.WriteLine("당신은 투표가 불가능 합니다..");
            }

            int time = 20;
            if (time < 18){
                Console.WriteLine("Good day.");
            }
            else{
                Console.WriteLine("Good evening.");
            }
            //삼항 연산자. 조건 ? 참 : 거짓.
            string result = (time < 18) ? "Good day." : "Good evening.";
            Console.WriteLine(result);

            //c# else if 문. 
            int time2 = 22;
            if (time2 < 10){
                Console.WriteLine("Good morning.");
            }
            else if (time2 < 20){
                Console.WriteLine("Good day.");
            }
            else{
                Console.WriteLine("Good evening.");
            }
            
            
        }
    }
}