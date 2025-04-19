namespace project0407
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("게임에 오신걸 환영합니다.");
            bool working = true;
            Random random = new Random();
            while (working)
            {
                Console.WriteLine("\n1.네자리 암호 맞추기");
                Console.WriteLine("2.숫자합 구하기.");
                Console.WriteLine("3.별찍기 프로그램.");
                Console.WriteLine("4.종료.");
                Console.Write("원하는 숫자를 입력해주세요: ");
                int choice = int.Parse(Console.ReadLine());
                switch (choice)
                {
                    case 1:
                        Console.WriteLine("숫자맞추기 게임입니다.");
                        int passwordnum = random.Next(1000, 10000);
                        String Password = passwordnum.ToString();
                        int trycount = 0;
                        String useranswer = "";
                        do
                        {
                            Console.Write("네자리 숫자를 입력해주세요.");
                            useranswer = Console.ReadLine();
                            if (useranswer == "0")
                            {
                                Console.WriteLine("게임을 종료합니다.");
                                break;
                            }
                            if (useranswer.Length != 4 || !useranswer.All(char.IsDigit))
                            {
                                Console.WriteLine("네자리숫자를 정확히 입력하세요");
                                continue;
                            }
                            trycount++;
                            int strike = 0;
                            int ball = 0;
                            for (int i = 0; i < 4; i++)
                            {
                                if (Password[i] == useranswer[i])
                                {
                                    strike++;
                                }
                                else if (Password.Contains(useranswer[i]))
                                {
                                    ball++;
                                }
                            }
                            Console.WriteLine($"{strike} 스트라이크, {ball}볼");

                            if (Password == useranswer)
                            {
                                Console.WriteLine("정답입니다!");
                                Console.WriteLine($"시도횟수:{trycount}");
                                break;
                            }
                        } while (useranswer != Password);
                        break;

                    case 2:
                        Console.WriteLine("\n숫자 맞추기 게임입니다,합이 100이면 종료됩니다.");
                        int sum = 0;
                        int tryplus = 0;
                        while (true)
                        {
                            Console.Write("숫자를 입력하세요(0을 입력하면 종료합니다.): ");
                            int inputnum = int.Parse(Console.ReadLine());
                            if (inputnum == 0)
                            {
                                Console.WriteLine("게임을 종료합니다.");
                                break;
                            }
                            if (inputnum < 1 || inputnum > 100)
                            {
                                Console.WriteLine("1~100이하의 숫자만 입력가능합니다.");
                                continue;
                            }
                            sum += inputnum;
                            tryplus++;
                            if (sum >= 100)
                            {
                                Console.WriteLine("100을 넘었습니다.");
                                Console.WriteLine($"시도횟수 {tryplus}");
                                break;
                            }
                        }
                        break;

                    case 3:
                        Console.WriteLine("\n별찍기 프로그램입니다.");
                        while (true)
                        {
                            Console.Write("원하는 높이를 입력해주세요. (0입력시 종료): ");
                            int height = int.Parse(Console.ReadLine());
                            if(height == 0)
                            {
                                Console.WriteLine("프로그램을 종료합니다.");
                                break;
                            }
                            if (height < 1)
                            {
                                Console.WriteLine("1이상의 수를 입력해주세요.");
                                continue;
                            }
                            for(int i= 1; i<=height; i++)
                            {
                                for(int j = 1; j<= i; j++)
                                {
                                    Console.WriteLine("*");
                                }

                                Console.WriteLine();
                            }
                            Console.WriteLine();
                        }
                        break;
                        
                    case 4:
                        Console.WriteLine("게임을 종료합니다.");
                        working = false;
                        break;

                    default:
                        Console.WriteLine("올바른 숫자를 입력하세요.");
                        break;

                }
            }
        }
    }
}