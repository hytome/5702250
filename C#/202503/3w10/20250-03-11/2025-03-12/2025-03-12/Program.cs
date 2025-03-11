namespace _2025_03_12
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //문자열 보간: 보간을 이용하면  +연산자 대신 더 간편하게 결합 가능하다.
            string onename = "HUHU";
            string Twoname = "HOHO";
            string fulname = $"my fullname is: {onename} {Twoname}";
            Console.WriteLine(fulname);
            //[] 이거 이용해서 문자열의 문자에도 접근가능하다.
            Console.WriteLine(onename[0]); //이렇게 타이핑하면 H가 나오는것. 
            //역순으로 특정 문자의 인덱스 위치도 찾을 수 있다.
            string myString = "Hello";
            Console.WriteLine(myString.IndexOf("e"));
            //또한 특정 문자를 찾은후 그곳을 기점으로 문자열 자르기도 할수있다.
            //찾기:IndexOf() 자르기:name.Substring()
            string name = "John Doe";
            int charPos = name.IndexOf("D");
            string lastname = name.Substring(charPos);
            Console.WriteLine(lastname); //output = Doe.
            //c# 백슬래시 시퀸스 문자. 
            //만약 출력문에서 따옴표를 표시하고 싶다면? 문법 오류를 막기위해 존재.
            string txt2 = "We are the so-called\"vikings\"from the north.";
            Console.WriteLine(txt2);
            string txt3 = "Hello\'world\'"; //작은 따옴표
            Console.WriteLine(txt3);
            string txt4 = "The charcter\\ is called backslash";
            Console.WriteLine(txt4);
            // \n:줄바꿈 \t:tab \b:backspace.


        }
    }
}
