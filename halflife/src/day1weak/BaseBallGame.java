package day1weak;
import java.util.*;
public class BaseBallGame {

    public void play(){
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();
        boolean keepPlaying = true;
        while(keepPlaying){
            List<Integer> answerList = new ArrayList<>();
            while(answerList.size() <3){
                int num  = rand.nextInt(9)+1; //야구 랜덤 설정. 배열의 1~9를 위해서 10이 아닌 9+1을 선정하는것.
                if(!answerList.contains(num)){
                    answerList.add(num); //숫자 중복 방지문,똑같은 숫자가 들어오지 않은 경우에만 배열에 추가하기.
                }

            }
            System.out.println("===숫자 야구 게임 시작.");
            System.out.println("3자리 숫자를 맞춰보세요. 중복 없음. 0 입력시 포기.");

            int tries = 0; //시도횟수.
            while (true){
                System.out.print("숫자입력: ");
                String input = sc.nextLine();
                if(input.equals("0")){ //게임 포기 예외 처리.
                    System.out.println("정답은"+answerList+"였습니다.");
                    break;
                }
                if(input.length()!=3 || !input.matches("[1-9]{3}")){
                    System.out.println("올바른 숫자를 입력해주세요.");

                }
            }
        }
    }
}
