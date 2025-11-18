package day2025_11_17;/*
 * =========================================
 *  프로그램 이름 : 카페 주문 시스템 시뮬레이터
 *  파일 이름    : CafeSimulator.java
 *
 *  작성 목적
 *      - 1~8강에서 배운 자바 기본 문법 + 객체지향 개념을 모두 적용해
 *        “카페 주문 과정”을 OOP 방식으로 모델링한다.
 *
 *  사용한 주요 개념 (강의 범위 1~8강)
 *  실행 흐름 개요
 *      1) 커스텀 옵션 안내 출력 (인터페이스 static 메서드)
 *      2) 메뉴 초기화 (Coffee / Latte / Tea / Seasonal)
 *      3) 할인 이벤트(Promotion) 익명 클래스로 정의
 *      4) 주문 개수 입력 → 반복문으로 각 주문 메뉴 선택
 *      5) make() 호출로 음료 한 잔씩 제조/커스텀/포장/서빙 처리
 *      6) 총액 계산 및 이벤트 할인 적용
 *
 *  사용법 (터미널)
 *      javac CafeSimulator.java
 *      java CafeSimulator
 *
 * =========================================
 *      - 추상화        : Beverage 추상 클래스
 *      - 상속          : Coffee, Latte, Tea 가 Beverage 상속
 *      - 캡슐화        : 음료 이름·가격 필드를 private 로 숨기고 getter 제공
 *      - 인터페이스    : Customizable, Takeout, Promotion
 *      - 다형성        : make(Beverage b) 에서 brew(), customize(), pack() 등 동적 호출
 *      - 업캐스팅      : new Coffee() → Beverage 타입 배열 저장
 *      - instanceof    : Customizable / Takeout 여부 판단
 *      - 익명 클래스    : Seasonal 메뉴, 임시 메뉴, Promotion 이벤트
 *      - 배열          : 메뉴 배열, 주문 배열 구조
 *      - 반복문        : 주문 입력/처리 루프
 *      - Scanner       : 사용자 입력 처리
 *
 */

import java.util.Scanner;

/* ===========================
 *  추상 클래스 : Beverage
 * ===========================
 * - 모든 음료의 공통 부모 클래스
 * - 이름(name), 가격(price) 보관
 * - brew() : 자식 클래스에서 반드시 구현해야 하는 추상 메서드
 * - serve() : 공통 제공 방식
 */
abstract class Beverage {
    private String name;  // 음료 이름 (캡슐화)
    private int price;    // 음료 가격 (캡슐화)

    Beverage(String name, int price) {
        this.name = name;
        this.price = price;
    }

    abstract void brew(); // 각 음료 클래스가 반드시 구현

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

/* ===========================
 *  인터페이스 : Customizable
 * ===========================
 * - customize() : 반드시 구현해야 하는 동작
 * - info()      : default 메서드(선택)
 * - guide()     : static 메서드(객체 없이 호출)
 */
interface Customizable {
    void customize();

    default void info() {
        System.out.println("커스텀 옵션을 적용합니다.");
    }

    static void guide() {
        System.out.println("옵션: 샷, 시럽, 우유온도 등");
    }
}

/* ===========================
 *  인터페이스 : Takeout
 * ===========================
 * - pack() : default 메서드 (포장)
 */
interface Takeout {
    default void pack() {
        System.out.println("포장컵에 담습니다.");
    }
}

/* ===========================
 *  Coffee 클래스
 * ===========================
 * - Beverage 상속
 * - Customizable + Takeout 구현
 */
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

/* ===========================
 *  Latte 클래스
 * ===========================
 * - Beverage 상속
 * - Customizable 구현
 */
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

/* ===========================
 *  Tea 클래스
 * ===========================
 * - Beverage 상속
 * - Customizable/Takeout 없음
 */
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

/* ===========================
 *  인터페이스 : Promotion
 * ===========================
 * - 할인 정책 추상화
 */
interface Promotion {
    int discount(int price);
}

/* ===========================
 *  메인 클래스 : CafeSimulator
 * ===========================
 */
public class CafeSimulator {

    /* -----------------------------------
     *  make(Beverage b)
     *  - 음료 한 잔 제조/커스텀/포장/서빙 로직
     *  - 다형성의 핵심이 실행되는 메서드
     * -----------------------------------
     */
    static void make(Beverage b) {

        // 1) 제조 단계 — 다형성: 실제 타입의 brew() 실행
        b.brew();

        // 2) Customizable 기능 여부 검사
        if (b instanceof Customizable) {
            Customizable c = (Customizable) b;
            c.info();       // 커스텀 안내
            c.customize();  // 실제 커스텀 작업
        }

        // 3) Takeout 기능 여부 검사
        if (b instanceof Takeout) {
            ((Takeout) b).pack(); // 포장 처리
        }

        // 4) 제공
        b.serve();

        // 5) 가격 출력
        System.out.println("가격: " + b.getPrice() + "원");
        System.out.println();
    }

    /* ===============================
     *  메인 실행부
     * ===============================
     */
    public static void main(String[] args) {

        // 1) 커스텀 가이드 출력 (인터페이스 static 호출)
        Customizable.guide();

        // 2) 메뉴 배열 생성
        Beverage[] menu = new Beverage[5];

        // 2-1) 정규 메뉴 등록
        menu[0] = new Coffee();
        menu[1] = new Latte();
        menu[2] = new Tea();

        // 2-2) 시즈널 메뉴 (익명 클래스)
        Beverage seasonal = new Beverage("시즈널 블렌드", 4200) {
            void brew() {
                System.out.println("시즈널 레시피로 제조합니다.");
            }

            void serve() {
                System.out.println("한정 메뉴를 특별 용기에 제공합니다.");
            }
        };
        menu[3] = seasonal;

        // 3) 할인 이벤트 정책 (Promotion 익명 구현 객체)
        Promotion event = new Promotion() {
            public int discount(int price) {
                return (int) (price * 0.8); // 20% 할인 적용
            }
        };

        // 4) 사용자 입력 처리
        Scanner sc = new Scanner(System.in);

        System.out.println("메뉴: 0)커피  1)라떼  2)티  3)시즈널  4)임시메뉴");
        System.out.print("주문 개수: ");
        int n = sc.nextInt();

        // 주문 배열 생성
        Beverage[] orders = new Beverage[n];

        // 4-1) n번 반복하며 주문 입력
        for (int i = 0; i < n; i++) {
            System.out.print("메뉴 번호 입력: ");
            int idx = sc.nextInt();

            if (idx == 4) {
                // 임시 메뉴 — 익명 클래스
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

        // 5) 주문 처리
        int sum = 0;

        for (int i = 0; i < orders.length; i++) {
            System.out.println("주문 #" + (i + 1) + " : " + orders[i].getName());
            make(orders[i]);               // 음료 한 잔 처리
            sum += orders[i].getPrice();   // 총액 계산
        }

        // 6) 총액 출력
        System.out.println("총액: " + sum + "원");

        // 7) 할인가 계산
        int discounted = event.discount(sum);

        // 8) 최종 결제 금액 출력
        System.out.println("이벤트 20% 적용가: " + discounted + "원");
    }
}
