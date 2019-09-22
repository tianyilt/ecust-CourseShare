interface Animal{
}
class Lion implements Animal{
	public String toString(){return "Lion" ;}
}
class Butterfly implements Animal{
	public String toString(){return "Butterfly" ;}
}

class  Cage <T>{
	T t;
	public void add(T t){this.t=t;	}
	public T get( ){
		System.out.print("  Cage: " );
		return t;	
	}	 
}
class  SubCage <T> extends Cage <T>{
	 
	public T get( ){
		System.out.print(" SubCage: " );
		return t;	
	 }
	public void prn( ){System.out.println(" "+t);	}	 
}

public class  TestSubtype3{
   public static void main(String[] args) 	{
	   // Animal lion=new Lion();
		//Animal butter=new Butterfly();
        Lion lion=new Lion();
		//Butterfly butter2=new Butterfly();

       // Cage<Animal> animalCage=new Cage<Animal>();
        Cage<Lion> lionCage=new Cage<Lion>();
        SubCage<Lion> subLionCage=new SubCage<Lion>();  
        lionCage.add(lion);
		subLionCage.add(lion);
		System.out.println(" "+lionCage.get());
		System.out.println(" "+subLionCage.get());


        lionCage=subLionCage;
		lionCage.add(lion);
		subLionCage.add(lion);
		System.out.println(" "+lionCage.get());//动态绑定，调用子范类的方法
		System.out.println(" "+subLionCage.get());
		 
	}
}
