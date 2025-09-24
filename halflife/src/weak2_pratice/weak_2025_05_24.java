package weak2_pratice;

public class weak_2025_05_24

{
    public static void main(String[] args) {
            int[][] gugudan = new int[9][9];

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    gugudan[i][j] = (i + 1) * (j + 1);
                }
            }


            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    System.out.printf("%d×%d=%-2d\t", i + 1, j + 1, gugudan[i][j]);
                }
                System.out.println();
            }
        }


}
