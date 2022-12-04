 abstract class Animal {
   protected String type, name,breed;
   public Animal(String type,String name,String breed){
      this.type=type;this.name=name;this.breed=breed;
    }
   public String toString(){
      return "This is a "+type+name+breed;
    }
   public abstract void sound();    //³éÏó·½·¨
 }


class Dog extends Animal{
   public Dog(String name){
     super("Dog",name,"Unknow");
   }
   public Dog(String name,String breed){
     super("Dog",name,breed);
  }
   public void sound(){ System.out.println("Woof Woof");  }
}
class Cat extends Animal{
   public Cat(String name){
     super("Cat",name,"Unknow");
   }
   public Cat(String name,String breed){
     super("Cat",name,breed);
   }
   public void sound(){System.out.println("Miiaooww");}
}
class Duck extends Animal{
   public Duck(String name){
     super(" Duck ",name,"Unknow");
  }
  public Duck(String name,String breed){
     super(" Duck ",name,breed);
  }
  public void sound(){
    System.out.println(" Quack quackquack ");
  }
}
 
public class TestAbstract{
  public static void main(String[] args){
   // Animal animal=new  Animal("Unknow","Unknow","Unknow");
    Animal animal=null;
    Dog dog=new Dog("Rover");
    Cat cat=new Cat("Max");
    Duck duck=new Duck("Daffy");
    animal=dog;
    animal.sound();
    animal=cat;
    animal.sound();
    animal=duck;
    animal.sound();
  }
}

