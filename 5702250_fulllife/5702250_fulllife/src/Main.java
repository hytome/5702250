/*
 * =========================================
 *  제출 파일 : main.java
 *
 *  수정 내용:
 *      - public class CafeSimulator → public class Main 으로 변경
 *      - 파일명 또한 main.java 로 변경하여 단일 파일 제출 가능하도록 맞췄습니다.
 *        프로그램 한줄 한줄의 주석은 지웠습니다.
 * =========================================
 */

import java.util.Scanner;

/* 추상 클래스 : Beverage */
abstract class Beverage {
    private String name;
    private int price;

    Beverage(String name, int price) {
        this.name = name;
        this.price = price;
    }

    abstract void brew();

    void serve() {
        System.out.println(name + "을(를) 제공합니다.");
    }

    String getName() {
        return name;
    }

    int getPrice() {
        return price;
    }
}

/* 인터페이스 : Customizable */
interface Customizable {
    void customize();

    default void info() {
        System.out.println("커스텀 옵션을 적용합니다.");
    }

    static void guide() {
        System.out.println("옵션: 샷, 시럽, 우유온도 등");
    }
}

/* 인터페이스 : Takeout */
interface Takeout {
    default void pack() {
        System.out.println("포장컵에 담습니다.");
    }
}

/* Coffee 클래스 */
class Coffee extends Beverage implements Customizable, Takeout {
    Coffee() {
        super("커피", 3000);
    }

    void brew() {
        System.out.println("원두를 추출합니다.");
    }

    public void customize() {
        System.out.println("샷을 추가합니다.");
    }
}

/* Latte 클래스 */
class Latte extends Beverage implements Customizable {
    Latte() {
        super("라떼", 3800);
    }

    void brew() {
        System.out.println("우유를 스팀하고 에스프레소와 섞습니다.");
    }

    public void customize() {
        System.out.println("우유 온도를 미온으로 조절합니다.");
    }
}

/* Tea 클래스 */
class Tea extends Beverage {
    Tea() {
        super("티", 2500);
    }

    void brew() {
        System.out.println("티백을 우립니다.");
    }

    void addLemon() {
        System.out.println("레몬을 추가합니다.");
    }
}

/* 할인 인터페이스 */
interface Promotion {
    int discount(int price);
}

/* =========================================
 *  여기!! public class CafeSimulator → Main
 * =========================================
 */
public class Main {

    static void make(Beverage b) {
        b.brew();

        if (b instanceof Customizable) {
            Customizable c = (Customizable) b;
            c.info();
            c.customize();
        }

        if (b instanceof Takeout) {
            ((Takeout)b).pack();
        }

        b.serve();
        System.out.println("가격: " + b.getPrice() + "원\n");
    }

    public static void main(String[] args) {

        Customizable.guide();

        Beverage[] menu = new Beverage[5];

        menu[0] = new Coffee();
        menu[1] = new Latte();
        menu[2] = new Tea();

        Beverage seasonal = new Beverage("시즈널 블렌드", 4200) {
            void brew() {
                System.out.println("시즈널 레시피로 제조합니다.");
            }
            void serve() {
                System.out.println("한정 메뉴를 특별 용기에 제공합니다.");
            }
        };
        menu[3] = seasonal;

        Promotion event = new Promotion() {
            public int discount(int price) {
                return (int)(price * 0.8);
            }
        };

        Scanner sc = new Scanner(System.in);

        System.out.println("메뉴: 0)커피  1)라떼  2)티  3)시즈널  4)임시메뉴");
        System.out.print("주문 개수: ");
        int n = sc.nextInt();

        Beverage[] orders = new Beverage[n];

        for (int i = 0; i < n; i++) {
            System.out.print("메뉴 번호 입력: ");
            int idx = sc.nextInt();

            if (idx == 4) {
                orders[i] = new Beverage("임시 메뉴", 3300) {
                    void brew() {
                        System.out.println("임시 레시피로 즉석 제조합니다.");
                    }
                };
            } else {
                orders[i] = menu[idx];
            }
        }

        System.out.println();
        int sum = 0;

        for (int i = 0; i < orders.length; i++) {
            System.out.println("주문 #" + (i + 1) + " : " + orders[i].getName());
            make(orders[i]);
            sum += orders[i].getPrice();
        }

        System.out.println("총액: " + sum + "원");

        int discounted = event.discount(sum);
        System.out.println("이벤트 20% 적용가: " + discounted + "원");
    }
}
