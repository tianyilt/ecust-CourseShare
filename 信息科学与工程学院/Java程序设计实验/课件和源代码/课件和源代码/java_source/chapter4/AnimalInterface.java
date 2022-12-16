  interface Animal {    
    String toString();       
    void sound();    //³éÏó·½·¨
   }

class Dog implements Animal{
   protected String type, name,breed;  
   public Dog(String name ){
	   this.type="Dog";
	   this.name=name;	   
   }
   public Dog(String name,String breed){
	   this.type="Dog";
	   this.name=name;
	   this.breed=breed;      
   }
   public String toString(){return "Dog";}
   public void sound(){ System.out.println("Woof Woof");  }
}


class Cat implements Animal{
  protected String type, name,breed;  
   public Cat(String name){
     this.type="Cat";
	   this.name=name;
    }
   public Cat(String name,String breed){
     this.type="Cat";
	   this.name=name;
	   this.breed=breed;    
   }
   public String toString(){return "Cat";}
   public void sound(){System.out.println("Miiaooww");}
}


class Duck implements Animal{   
  protected String type, name,breed;  
  public Duck(String name){
	  this.type="Duck";
	   this.name=name;	  
  }
  public Duck(String name,String breed){
	  this.type="Duck";
	   this.name=name;
	   this.breed=breed;       
  }
  public String toString(){return "Duck";}
  public void sound(){
    System.out.println(" Quack quackquack ");
  }
}
 
public class  AnimalInterface{
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

