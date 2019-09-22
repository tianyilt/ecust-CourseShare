
public class  TestPerson2 {	
	
	public static void f1(){
	     Person tom=new Person(1,"tom","ÄÐ" );
		 tom.school="FUDAN"; 
		 tom.speak(); 
	}

	public static void f2(){
	     Person rose=new Person(2,"rose","Å®" );
		 rose.speak();	
	}
	public static void main(String[] args) 	{  
		 f1();
		 f2();
	}
}
