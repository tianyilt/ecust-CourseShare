public class   TestInherit2
{
	public static void main(String[] args) 
	{
		Teacher tom=new Teacher( 1,"tom","男","计算机系","教授",6000); 
        tom.speak();
        

 	
	 

       // Teacher jack=new Teacher( 1,"jack","男","计算机系","教授",6000); 
        Teacher jack=new Teacher(  ); 
		jack.setNo(1);       //继承父类的方法
		jack.setName("jack");   //继承父类的方法
		jack.setSex("男");   //继承父类的方法
		jack.setDepartment("计算机系");
		jack.setTitle("教授");
		jack.setSalary(6000); 
        System.out.println("教师: "+"  学校:"+Person.school+"    编号:"+jack.getNo()+"    姓名:"+jack.getName()+"    性别:"+jack.getSex()+" 所在部门:"+jack.getDepartment()+"  职称: "+jack.getTitle()+" 工资:"+jack.getSalary() );
		  //Person.school: 继承父类的成员变量

     //   jack.school="fudan";

		//Person p1=new Person();
       // System.out.println( "  学校:"+Person.school);

		//System.out.println(tom.equals(tom));
	}
}
