class  Student
{
	String no;
	int age;
	public  Student(){
	}
	public   Student(String no2,int age2){
     no=no2;
	 age=age2;
	}
    public void Student(Student student2){
     no=student2.no;
	 age=student2.age;
	}
   public void  ChangeStudent(Student student2){ 
	   student2.age++; 
	   return;
   } 
};

public class StudentTest
{
	public static void main(String[] args){
		  Student tom=new Student("001",20);
		  System.out.println(tom.age);
		  tom.ChangeStudent(tom);
		  System.out.println(tom.age); 
	}

};
