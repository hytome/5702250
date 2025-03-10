using System;

namespace helloworld {
//c#에서 namespace는 관련된 클래스,인터페이스등을 그룹화 하는데 유용합니다.
//마치 컨테이너 처럼 관련된 클래스들을 묶어서 관리할 수 있습니다.
//이러한 방식으로 그룹화를 하면 다른 컨테이너에서 동일한 이름의 클래스를 사용할 수 있습니다. (충돌 x)
//예를 들어, 두 개의 라이브러리가 있고 각각 동일한 이름의 클래스를 가지고 있을 때, 이름 충돌을 방지하기 위해 네임스페이스를 사용할 수 있습니다.

    class Program { 
        //c#에서 class는 클래스를 정의하는 키워드입니다.
        //클래스는 객체 지향 프로그래밍(OOP)의 기본 단위입니다.
        //클래스는 데이터(속성)와 기능(메서드)을 하나로 묶어서 객체를 생성하는데 사용됩니다.
        //예를 들어, 사람을 나타내는 클래스가 있고, 이 클래스는 이름, 나이, 성별 등의 속성과
        // 인사하기, 걷기 등의 메서드를 가질 수 있습니다.
        static void Main(string[] args){
            //단순한 문장 출력문.
            Console.WriteLine("Hello World");
            Console.WriteLine(3 + 3);
            //변수 선언 하고 사용해보기.
            string name = "heo";
            Console.WriteLine(name);
            int age = 15;
            Console.WriteLine(age);
            //변수를 먼저 선언하고 나중에 값을 할당하는 방식도 가능하다.
            int mynum;
            mynum = 10;
            Console.WriteLine(mynum);
            //새 값을 할당하여 덮어 씌울수도 있다.
            int myage = 20;
            myage = 25;
            Console.WriteLine(myage);
            //변경할수 없는 상수 도 존재합니다. 이러한 상수선언을 하면 읽기전용만 가능합니다.
            const double pi = 3.14;
            Console.WriteLine(pi);
            // pi = 3.15; 이렇게 하면 오류 발생.
            //디스 플레이 변수:변수 의 값을 출력한다는 뜻입니다. 
            string firstname = "jo";
            Console.WriteLine("hello " + firstname);
            int year = 2025;
            int month = 3;
            int day = 5;
            // 문자열 보간법을 사용하여 변수의 값을 포함시킴
            string today = $"{year}년 {month}월 {day}일";
            //이렇게 변수를 문자열에 포함시키면 변수의 값을 문자열에 포함시킬수 있습니다.
            Console.WriteLine(today);

        }
    }
}