package weak3_pratice;

public class weak3_10_01 {
    public static  int add(int a, int b){
        return a+b;
    }

    public static int greeting(String name){
        System.out.println("Hello, " + name);
        return 0;
    }

    public static void main(String[] args) {
        System.out.println(add(1,2));
        System.out.println(greeting("John"));
    }

}
