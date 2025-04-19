namespace program0411
{
    //클래스는 Student로 해야한다.
    //다음 인스턴스 변수는 외부에서 건들수 없도록 private로 만든다.(늘어나는 학생의수, 이름,나이,국어점수,수학점수. ->완료.
    //학생 객체가 생성 될때마다 totalcount ++ 


    class Student
    {

        public static int totalcount = 0;
        public int id;
        private string name;
        private int age;
        private int koreanscore;
        private int mathscore;
        public int totalscore = 0;
        public float average = 0;

        public Student(string inputname, int inputage)
        {
            totalcount++;
            id = totalcount;
            name = inputname;
            age = inputage;
        }

        public void SetScores(int inputKoreanscore, int inputmathscore)
        {
            koreanscore = inputKoreanscore;
            mathscore = inputmathscore;     
        }

        public float CalculateAverage() {
            totalscore = koreanscore + mathscore;
            average  = totalscore / 2;
            return  average;

        }
        
        public void Displayinfo()
        {
            Console.WriteLine($"이름:{name}\n 나이:{age}\n 국어점수:{koreanscore}\n 수학점수:{mathscore}");
            Console.WriteLine(CalculateAverage());
            if (CalculateAverage() < 60)
            {
                Console.WriteLine("불합격 입니다.");
            }
        }

    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
        }
    }
}
