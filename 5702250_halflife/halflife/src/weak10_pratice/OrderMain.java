package weak10_pratice;

import java.util.Scanner;

public class OrderMain {
    static class Order {
        private String customer;
        private Item[] items = new Item[5];
        private int count;

        Order(String customer) { this.customer = customer; }

        void addItem(Item item) {
            if (count < items.length) {
                items[count++] = item;
                System.out.println(item.name + " 추가");
            } else {
                System.out.println("장바구니가 가득 찼습니다");
            }
        }

        void printOrder() {
            System.out.println("고객: " + customer);
            int sum = 0;
            for (int i = 0; i < count; i++) {
                System.out.println("- " + items[i].name + " : " + items[i].price + "원");
                sum += items[i].price;
            }
            System.out.println("합계: " + sum + "원");
        }

        static class Item {
            String name;
            int price;
            Item(String name, int price) { this.name = name; this.price = price; }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Order order = new Order("홍길동");

        System.out.println("아이템 개수 입력(최대 5):");
        int n = sc.nextInt();
        if (n > 5) n = 5;
        sc.nextLine();

        for (int i = 0; i < n; i++) {
            System.out.print("이름: ");
            String name = sc.nextLine();
            System.out.print("가격: ");
            int price = sc.nextInt();
            sc.nextLine();
            order.addItem(new Order.Item(name, price));
        }

        System.out.println();
        order.printOrder();
    }
}

