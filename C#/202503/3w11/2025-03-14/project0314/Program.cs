using System;

namespace Project0314
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("===학생 성적 관리 프로그램===\n");
            Console.Write("학생 이름을 입력하세요: ");
            string stuname = Console.ReadLine();
            Console.Write("학번을 입력하세요: ");
            string stunum = Console.ReadLine();
            Console.Write("응시한 과목수를 입력하세요: ");
            int titlecount = int.Parse(Console.ReadLine());

            Console.Write("과목 명을 차례로 입력하세요 (공백으로 구분): ");
            string inputTitles = Console.ReadLine();
            string[] titles = inputTitles.Split(' '); // 공백으로 분리하여 배열 생성
            titlecount = titles.Length; // 배열의 길이를 통해 과목 수 결정

            
            int[] scores = new int[titlecount];
            for(int i = 0; i < titlecount; i++){
                Console.Write(titles[i]+" 점수를 입력하세요: ");
                scores[i] = int.Parse(Console.ReadLine());
                Console.WriteLine(titles[i]+ "점수 입력 완료.");
            }
            Console.WriteLine("\n[결과 출력]");
            for(int i = 0; i<titlecount; i++){
                Console.WriteLine(titles[i]+" : "+scores[i]);
            }
            //총점과 평균 계산
            int total = 0;
            double average = 0.0;
            for(int i = 0; i < titlecount; i++){
                total += scores[i];
            }
            average = (double)total / titlecount;
            Console.WriteLine("총점: "+total);
            Console.WriteLine("평균: "+average);
        }
    }
}

