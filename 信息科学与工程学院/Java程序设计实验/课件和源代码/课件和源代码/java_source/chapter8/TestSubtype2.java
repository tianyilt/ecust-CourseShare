interface Animal{}
class Lion implements Animal{
   public String toString(){return "Lion" ;}
}
class Butterfly implements Animal{
	public String toString(){return "Butterfly" ;}
}

class  Cage <T>{
	T t;
	public void add(T t){this.t=t;	}
	public T get( ){return t;	}
	 
}
public class  TestSubtype2{
   public static void main(String[] args) 	{
	    Cage<Animal> animalCage=new Cage<Animal>();
		Animal animal=null;

		Lion lion=new Lion();
		Butterfly butter=new Butterfly();
        
		animal=butter; 
		animalCage.add(animal);
		System.out.println(" "+animalCage.get());

        animal=lion; 
        animalCage.add(lion);
		System.out.println(" "+animalCage.get()); 

		Cage<Lion> lionCage=new Cage<Lion>();
		 
        
        lionCage.add(lion); 
		System.out.println( lionCage.get());  
		/*
		lionCage.add(animal); //编译出错,静态绑定的原因
		System.out.println("Hello World!"+lionCage.get()); 
		*/
 
      //  animalCage=lionCage;//不兼容的类型 ,Cage<Lion>不是Cage<Animal>的子类

	}
}
