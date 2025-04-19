using System.Runtime.InteropServices;

namespace project04072
{
    class Program
    {
        static void Main(string[] args)
        {
            Gamemenu menu = new Gamemenu();
            menu.start();
        }
    }

    class Gamemenu
    {
        public void start()
        {
            bool working = true;
            while (working)
            {
                Console.WriteLine("==게임에 오신걸 환영합니다.==");
                Console.WriteLine("==1.암호맞추기 게임\n==2. 숫자 맞추기 게임 \n==3.종료.");
                Console.Write("플레이할 게임을 입력해주세요: ");
                int choise = int.Parse(Console.ReadLine());


                switch (choise)
                {
                    case 1:
                        Passwordgame.play();
                        break;
                    case 2:
                        Passwordgametwo.play();
                        break;
                    case 3:
                        Console.WriteLine("게임을 종료합니다.");
                        working = false;
                        break;
                    default:
                        Console.WriteLine("1~3사이의 숫자만 입력해주세요.");
                        break;
                }
            }
        }

        //숫자 네자리 암호 맞추기 퀴즈.
        class Passwordgame
        {
            public static void play()
            {
                String useranswer = "";
                Random random = new Random();
                string password = random.Next(1000, 10000).ToString();
                int trycount = 0;
                string trycountresult = (trycount < 3) ? "대단한 솜씨입니다..." : "수고하셨습니다!";

                do
                {
                    Console.Write("4자리 숫자를 입력해줘,0을 누르면 종료야: ");
                    useranswer = Console.ReadLine();
                    if (useranswer == "0")
                    {
                        Console.WriteLine("게임을 종료합니다.");
                        break;
                    }
                    if (useranswer.Length != 4 || !useranswer.All(char.IsDigit))
                    {
                        Console.WriteLine("4자리 숫자를 입력해주세요");
                        continue;
                    }
                    trycount++;
                    int strike = 0;
                    int ball = 0;
                    for (int i = 0; i < password.Length; i++)
                    {
                        if (password[i] == useranswer[i])
                        {
                            strike++;
                        }
                        else if (password.Contains(useranswer[i]))
                        {
                            ball++;
                        }
                        Console.WriteLine($"{strike}스트라이크 {ball} 볼 입니다!");
                    }
                    if (password == useranswer)
                    {
                        Console.WriteLine($"정답입니다! 시도횟수는 {trycount} 입니다!");
                        Console.WriteLine(trycountresult);
                        break;
                    }

                } while (password != useranswer);
            }
        }
        //숫자 맞추기 게임 시작 클래스.
        class Passwordgametwo
        {
            public static void play()
            {
                Console.WriteLine("== 숫자 맞추기 게임에 오신걸 환영합니다.");
                Random random = new Random();
                int password = random.Next(1, 51);
                int trycount = 1;
                string trycountresult = (trycount < 4) ? "대단한 솜씨입니다.." : "수고하셨습니다.";
                int usernum = 0;

                do
                {
                    Console.Write("숫자를 입력해주세요. 0을 입력하면 종료됩니다.: ");
                    usernum = int.Parse(Console.ReadLine());
                    if (usernum == 0)
                    {
                        Console.WriteLine("게임을 종료합니다.");
                        break;
                    }
                    if (usernum > 50)
                    {
                        Console.WriteLine("암호는 1~50까지 입니다. 범위 내의 숫자를 입력해주세요.");
                        continue;
                    }
                    if (usernum > password)
                    {
                        Console.WriteLine($"정답은 {usernum}보다 작은 수입니다.");
                        trycount++;
                    }
                    if (usernum < password)
                    {
                        Console.WriteLine($"정답은 {usernum}보다 큰 수입니다.");
                        trycount++;
                    }
                    if (usernum == password)
                    {
                        Console.WriteLine($"축하합니다. 정답은 {password} 였습니다! 시도횟수:{trycount}");
                        Console.WriteLine(trycount);
                    }

                } while (password != usernum);
            }
        }
    }
}
