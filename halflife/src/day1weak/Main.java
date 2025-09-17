package day1weak;
import java.util.Scanner;


public class Main {

    public static void main(String[] args) {
            Scanner sc = new Scanner(System.in); //프로그램 인풋 넣을 값을 위한 기능.
            int choice;
            //프론트 cli 구현
            while(true){
                System.out.println("===자바 연습 프로젝트");
                System.out.println("1.업앤 다운 게임");
                System.out.println("2.숫자 야구 게임");
                System.out.println("0.프로그램 종료");
                System.out.print("메뉴 선택: ");
                choice = sc.nextInt(); //숫자 입력 받는 값.

                switch (choice) {
                    case 1:
                        UpDownGame updown = new UpDownGame();
                        updown.play();
                        break;
                    case 2:
                        BaseBallGame baseball = new BaseBallGame();
                        baseball.play();
                        break;
                    case 0:
                        System.out.println("프로그램을 종료합니다.");
                        return;
                    default:
                        System.out.println("잘못된 입력입니다.");
                }

            }
    }
}
