package weak2_pratice;
import java.util.Scanner;

public class weak2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // 첫 번째 숫자 검사
        int num = sc.nextInt();
        if (num > 10) {
            System.out.printf("%d는 10보다 큽니다.\n", num);
        } else {
            System.out.printf("%d는 10보다 작거나 같습니다.\n", num);
        }

        // 짝수/홀수 검사
        int num2 = sc.nextInt();
        if (num2 % 2 == 0) {
            System.out.printf("%d는 짝수입니다.\n", num2);
        } else {
            System.out.printf("%d는 홀수입니다.\n", num2);
        }


        String id = "abcdefg";
        int password = 1234;

        System.out.print("아이디를 입력하세요: ");
        String id2 = sc.next();

        if (!id.equals(id2)) {
            System.out.println("아이디가 일치하지 않습니다.");
        } else {
            System.out.print("비밀번호를 입력해주세요: ");
            int password2 = sc.nextInt();

            if (password != password2) {
                System.out.println("비밀번호가 일치하지 않습니다.");
            } else {
                System.out.println("로그인 성공!");
            }
        }
    }
}
