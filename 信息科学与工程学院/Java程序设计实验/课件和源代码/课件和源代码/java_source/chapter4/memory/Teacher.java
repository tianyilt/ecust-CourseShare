public class  Teacher extends Person  //教师类
{ 
	private String department;  //所在部门
	private String title;  //职称
	private double salary;  //工资 

	public Teacher(){} 

	public Teacher(int No,String name,String sex,String department,String title,double salary ){
	   // super( No, name, sex);
	  // this.No=No; this.name=name;this.sex=sex;// 不可访问  
	    setNo(No);setName(name);setSex(sex); 
       this.department=department; this.title=title; this.salary=salary; 
	}
    public void setDepartment(String department){ this.department=department;}
	public String getDepartment(){ return department;} 

	public void setTitle(String title){ this.title=title;}
	public String getTitle(){return this.title;}

	public void setSalary(double salary){this.salary=salary;}
	public double getSalary(){return this.salary;}
	 
	public void speak(){ 
	  // System.out.println("教师: "+"  学校:"+school+"    编号:"+No+"    姓名:"+name+"    性别:"+sex+" 所在部门:"+department+"  职称: "+title+" 工资:"+salary );
	
	   System.out.println("教师: "+"  学校:"+Person.school+"    编号:"+getNo()+"    姓名:"+getName()+"    性别:"+getSex()+" 所在部门:"+department+"  职称: "+title+" 工资:"+salary );
	
	  //System.out.println("教师: "+"  学校:"+Person.school+"    编号:"+this.getNo()+"    姓名:"+this.getName()+"    性别:"+this.getSex()+" 所在部门:"+this.department+"  职称: "+title+" 工资:"+this.salary );
	
	}
}
