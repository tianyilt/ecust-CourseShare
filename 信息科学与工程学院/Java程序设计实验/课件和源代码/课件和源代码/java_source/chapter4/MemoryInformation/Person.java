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

	public String toString(){return "Person类";}
 
	public static void main(String[] args) 	{
		String  name=null; 
		String id=null;
		int  age=0; 
		Person tom=new Person(); 
		tom.setName("Tom");
		tom.setId("3301");
		tom.setAge(19); 
		
		name=tom.getName();
		id=tom.getId();
		age=tom.getAge();
		
		System.out.println( name);
		System.out.println( id);
		System.out.println( age);

		System.out.println(tom.toString());
	}
}
