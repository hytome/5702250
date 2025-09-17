package day1weak;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;
public class UpDownGame {

    public void play() {
        Scanner sc = new Scanner(System.in);
        Random rand = new Random(); //랜덤 변수 생성.
        boolean keepPlaying = true;
        while (keepPlaying) {
            int min, max; //최대값 최소값 설정.
            while (true) {
                try {
                    System.out.print("최소값을 입력하세요");
                    min = sc.nextInt();//이게 숫자 Read하는 느낌?
                    System.out.print("최대값을 입력하세요");
                    max = sc.nextInt();
                    //최소값 최대값 예외 처리를 위한 조건문 생성.
                    if (min >= max) {
                        System.out.println("최소값이 최대값을 넘었습니다!");
                        sc.nextLine(); //잘못된 입력 버퍼 제거 라고 하네요.
                    } else {
                        break;
                    } //예외 처리 끝. 이어서 숫자,즉 정수만 입력했는지 예외처리.
                } catch (InputMismatchException e) {
                    System.out.println("숫자만 입력해주세요");
                    sc.nextLine();//버퍼 제거.
                }

            }//여기 까지가 예외처리 끝 이걸로 최소값 최대값이 정상으로 작동하고 정수형만 입력된다.

            int answer = rand.nextInt(max - min + 1) + min;//min~max범위.
            int guess; //입력한 숫자 넣는용도.
            int tries = 0; //시도횟수
            //본격적인 게임 시작.
            System.out.printf("=== 업다운 게임을 시작합니다! (%d ~ %d)===",min,max);
            System.out.println("게임을 포기하려면 0을 입력하세요.");
            while (true) {
                try {
                    System.out.print("숫자 입력: ");
                    guess = sc.nextInt();
                    tries++;
                    if(guess == 0) {
                        System.out.println("게임을 포기하셨습니다.");
                        System.out.println("정답은"+ answer+ "입니다.");
                        System.out.println("시도횟수" +tries);
                    }else if (guess == answer) {
                        System.out.println("축하합니다" + tries + "회 만에 정답을 맞추셨습니다.");
                        break;
                    } else if (guess < answer) {
                        System.out.println("업!");

                    } else {
                        System.out.println("다운");
                    }

                } catch (InputMismatchException e) {
                    System.out.println("숫자만 입력해라이!");
                    sc.nextLine();
                }

            }
            System.out.print("다시 하시겠습니까(y/n)");
            String retry = sc.next();
            if(!retry.equals("y")) {
                keepPlaying = false;
                System.out.println("게임을 종료합니다. ");
            }
        }
    }
    }



