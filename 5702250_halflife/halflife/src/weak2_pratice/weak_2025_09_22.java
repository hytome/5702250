package weak2_pratice;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class weak_2025_09_22 {
    public static void main(String[] args) {
        System.out.println("5명의 성적을 입력하세요:");
        List<Integer> list = new ArrayList<>();
        Scanner sc = new Scanner(System.in);

        int sum = 0;  // 총합 저장용
        for (int i = 0; i < 5; i++) {
            int score = sc.nextInt();
            list.add(score);
            sum += score;
        }

        double avg = (double) sum / list.size();
        System.out.printf("평균은 %.2f 입니다.%n", avg);


    }
}
