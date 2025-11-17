package weak7_pratice2;

abstract  class Animal{
    String name;
    Animal(String name){
        this.name=name;
    }
    int age;

    Animal() {
    }

    void eat(){}
    abstract void sleep();
    void Wagtail(){}

}

class Dog extends Animal{
    void sleep(){}
 void bark(){
     System.out.println("왈왈 짖습니다.");
 }
}
public class weak7_2025_10_22 {

    public static void main(String[] args) {
        Animal d= new Dog();
        Dog d1=new Dog();
        d1.name = "강아지";
        d1.age=10;
        d1.eat();
        d1.sleep();
    }
}
