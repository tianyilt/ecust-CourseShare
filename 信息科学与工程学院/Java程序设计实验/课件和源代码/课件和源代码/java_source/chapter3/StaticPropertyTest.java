//程序功能要求能自动计算出当前的Employee的No号.
class Employee{
  String name;  int employeeNo ;
  static int id=0;
  public Employee(String sName){
    employeeNo=++id;   name=sName;
  }
}     
public class StaticPropertyTest{
  public static void main(String[]  args){
    Employee zhang=new Employee("zhang");
    Employee wang=new Employee("wang");
    Employee li=new Employee("li");

    System.out.println(zhang.employeeNo);
    System.out.println(wang.employeeNo);
    System.out.println(li.employeeNo);
    System.out.println(Employee.id);
   }
}
