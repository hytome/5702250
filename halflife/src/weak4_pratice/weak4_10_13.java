package weak4_pratice;


class Car{
    String color;
    int number;


    void drive(){
        color = "빨간색";
        number = 5413;
        System.out.printf("%s %d 번 자동차가 달립니다.",color,number);
    }
}
public class weak4_10_13 {
    public static void main(String[] args) {
        Car car = new Car();
        car.drive();
    }


}
