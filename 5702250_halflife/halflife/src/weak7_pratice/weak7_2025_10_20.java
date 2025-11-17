package weak7_pratice;

class Animal {
    String name;
    int age;
    Animal(String name) {
        this.name = name;
        System.out.printf("Animal's name is: %s\n", name);
    }
    void sound() {
        System.out.print("동물이 짖습니다.\n");
    }

}

class Dog extends Animal {
    String breed;
    Dog(String name) {
        super(name);
    }
    void roll() {
        System.out.println(name + "가 구르고 있습니다.");
    }
    void sound() {
        System.out.println(name + "가 멍멍 짖습니다!");
    }
}

class Cat extends Animal {
    Cat(String name) {
        super(name);
    }
    void rub() {
        System.out.println(name + "가 몸을 비비고 있습니다.");
    }
    void sound() {
        System.out.println(name + "가 야옹 하고 웁니다!");
    }
}

public class weak7_2025_10_20 {
    public static void main(String[] args) {
        Dog dog = new Dog("바둑이");
        dog.age = 3;
        dog.breed = "진돗개";
       ;
        dog.roll();
        dog.sound();

        System.out.println();

        Cat cat = new Cat("나비");
        cat.age = 2;

        cat.rub();
        cat.sound();
    }
}
