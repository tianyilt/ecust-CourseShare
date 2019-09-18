class Animal{
 protected String type;  //种类
 protected String name;  //名称
 protected String breed; //品种
 
 public Animal(String type,String name,String breed){
     this.type=type;this.name=name;this.breed=breed;
  }
 public String toString(){   return "This is a "+type+name+breed; }
 public void sound(){}
}

class Dog extends Animal{
  public Dog(String name){super("Dog",name,"Unknow");}
  public Dog(String name,String breed){super("Dog",name,breed);}
  public void sound(){System.out.println("Woof Woof");}
}

class Cat extends Animal{
  public Cat(String name){super("Cat",name,"Unknow");}
  public Cat(String name,String breed){super("Cat",name,breed);}
  public void sound(){System.out.println("Miiaooww");}
}

class Duck extends Animal{
  public Duck(String name){     super(" Duck ",name,"Unknow");  }
  public Duck(String name,String breed){     super(" Duck ",name,breed);  }
  public void sound(){    System.out.println(" Quack quackquack ");  }
}

public class TestPolymorphism {
  public static void main(String[] args){
    Animal animal=new  Animal("Unknow","Unknow","Unknow");
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
