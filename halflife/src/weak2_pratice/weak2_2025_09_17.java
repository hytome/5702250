package weak2_pratice;
import java.util.Scanner;
public class weak2_2025_09_17
{
    public static void main(String[] args) {
        int sum = 0;
        Scanner sc = new Scanner(System.in);
        System.out.print("단을 입력하세요: ");
        sum = sc.nextInt();
        for(int i=1; i<=9;i++)
        {

            System.out.printf("%d * %d = %d \n",sum,i,sum*i);
        }

        for(int x=1; x<=9; x++){
            for(int y=1; y<=9; y++){
                System.out.printf("%d * %d = %d \n",x,y,x*y);
            }
        }

        while(true){
            System.out.print("단입력: ");
            int dan = sc.nextInt();
            if(dan==0){
                break;
            }
        }
        int i= 1;
        while(i<=9){
            System.out.printf("%d * %d = %d" ,dan, i, dan*i );
            i++;
        }
    }
}
