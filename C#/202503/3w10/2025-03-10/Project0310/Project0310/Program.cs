namespace Project0310
{
    internal class Program
    {
        static void Main(string[] args)
        {  //c#에는 자동 형변환이 존재한다.
            //예를 들면 int를 double로 바꾸거나 기타등등. 
            int myint = 9;
            double mydouble = myint;
            Console.WriteLine(myint);
            //그러나 반대의 경우에는 괄호로 묶어서 수동으로 수행 해야합니다.
            //왜냐하면 int 는 정수만 저장하기 떄문 따라서 우리가 수동으로 수행해야한다.
            double youdouble = 9.67;
            int youint = (int) youdouble; //이러면 outpuy이 9로 성공적으로 나온다.
            //이런 방식으로 말이다.
            //또한 내장 메서드를 이용하여 출력문에서 이용할수있다.
            //convert.To(문자형)를 이용하면된다.
            //여기서 문자형을 int로 convert하고 싶은경우 int 32 64이렇게 설정해줘야 한다.
            int weint = 10;
            double wedouble = 5.25;
            bool myBool = true;
            Console.WriteLine(Convert.ToString(weint)); //string형태로 10출력.
            Console.WriteLine(Convert.ToDouble(weint)); // double형태로 int 출력.
            Console.WriteLine(Convert.ToInt32(wedouble)); //int형태로 double출력.
            Console.WriteLine(Convert.ToString(myBool)); //string 형태로 bool출력.




            Console.WriteLine("Hello, World!");
        }
    }
}
