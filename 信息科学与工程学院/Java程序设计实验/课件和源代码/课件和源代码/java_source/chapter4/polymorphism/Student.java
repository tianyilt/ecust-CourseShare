class Person{
	public String name;//姓名
	public String Id; //身份证 
	private int   age;  //年龄 ：私有属性

	public Person(){	}
	public Person(String name,String Id, int age){	
	    this.name=name; this.Id=Id;  this.age=age;
	}
    
	public void setName(String name){ this.name=name;}
	public String getName(){return name;}

	public void setId(String Id){ this.Id=Id;}
	public String getId(){return Id;}

	public void setAge(int age){ this.age=age;}
	public int getAge(){return age;} 

	public String toString(){return "Person类: "+name+" "+Id+" "+age;}
}
class  Teacher  extends Person{
	public String no;//工号
	public String school; //学校 
	public String department; //系别 
	public int salary; //薪水 
    
	public Teacher(){	}
	public Teacher(String name,String Id, int age,
		String no,String school,String department,int salary ){	
	    this.name=name; this.Id=Id;  setAge(age);
		this.no=no;this.school=school; this.department=department; this.salary=salary; 
	}
	public void setNo(String no){ this.no=no;}
	public String getNo(){return no;}

	public void setSchool(String school){ this.school=school;}
	public String getSchool(){return school;}

    public void setDepartment(String department){ this.department=department;}
	public String getDepartment(){return department;}

	public void setSalary(int salary){ this.salary=salary;}
	public int getSalary(){return salary;}

    //overriding
    public String toString(){return "Teacher类: "+name+" "+Id+" "+no+" "+school+" "+department+" "+salary;}

}
public class  Student  extends Person{
	public String no;//学号
	public String school; //学校 
    
	public Student(){	}
	public Student(String name,String Id, int age,
		String no,String school ){	
	    this.name=name; this.Id=Id;  setAge(age);
		this.no=no;this.school=school; 
	}

	public void setNo(String no){ this.no=no;}
	public String getNo(){return no;}

	public void setSchool(String school){ this.school=school;}
	public String getSchool(){return school;}

    //overriding 
    public String toString(){return "Student类: "+name+" "+Id+" "+no+" "+school ;}

	public static void main(String[] args) 	{
		 Person p=null;

		 Person jack=new Person();
		 jack.setName("Jack");
		 jack.setId("3300");
		 jack.setAge(20); 
         
		 Student tom=new Student(); 
		 tom.setName("Tom");
		 tom.setId("3301");
		 tom.setAge(19); 
		 tom.setNo("2006");
		 tom.setSchool("Ecust"); 

         Teacher rose=new Teacher(); 
		 rose.setName("Rose");
		 rose.setId("3301");
		 rose.setAge(19); 
		 rose.setNo("01111");
		 rose.setSchool("Ecust"); 
		 rose.setDepartment("Computer");
		 rose.setSalary(2000); 

		 p=jack;
		 System.out.println(p.toString()); 
         p=tom;
		 System.out.println(p.toString()); 
		 p=rose;
		 System.out.println(p.toString()); 

	}
}
