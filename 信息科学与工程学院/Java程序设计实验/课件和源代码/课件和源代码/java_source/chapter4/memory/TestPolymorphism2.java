
public class   TestPolymorphism2{
	public static void main(String[] args)	{
		Person p=null;
		Teacher tom=new Teacher( 1,"tom","男","计算机系","教授",6000); 
		Student rose=new Student(11,"rose","女","计算机",600);
		
		p=tom;
        p.speak(); 
		p=rose;
        p.speak(); 
	}
}



 
