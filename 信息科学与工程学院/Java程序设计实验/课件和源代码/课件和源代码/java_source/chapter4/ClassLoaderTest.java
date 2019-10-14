 
class ClassLoaderTestParent{
  static {
      System.out.println("  ִ�и����е�static�顡�� ");
  }
  public static int age1=getAge1();
  public String str1=getString1();

  public ClassLoaderTestParent(){
	  System.out.println("  ִ�и���Ĺ��췽����ClassLoaderTestParent()");
	  System.out.println();
  }

  public static int  getAge1(){
	  System.out.println("  �������е������age1��ֵ:��getAge1()");
	  return 1;
  }

  public static String getString1(){
	  System.out.println("  �������е�ʵ������str1��ֵ:��getString1()");
	  return "String ";
  }

  { 
	  System.out.println("  ִ�и����е� ʵ���顡���� ");
	  
  }   
}


public class ClassLoaderTest extends ClassLoaderTestParent{
 static {
       System.out.println("  ִ�������е�static�顡 ");
  }
  public static int age2=getAge2();
  public String str2=getString2();

  public ClassLoaderTest(){
	  super();
	  System.out.println("  ִ������Ĺ��췽����ClassLoader()");
  }

  public static int  getAge2(){
	  System.out.println("  �������е������age2��ֵ:getAge2()");
	  return 2;
  }

  public static String getString2(){
	  System.out.println("  �������е�ʵ������str2��ֵ:getString2()");
	  return "String2 ";
  }

  { 
	  System.out.println("  ִ�������е� ʵ���� ");
	  
  }
  

  public static void main(String[] args){

    

	ClassLoaderTest c1;
    System.out.println("----------------before new----------------- ");
	c1=new ClassLoaderTest();
	System.out.println("----------------after new------------------ ");
  }
}

/*���  

  ִ�и����е�static�顡�� 
  �������е������age1��ֵ:��getAge1()
  ִ�������е�static�顡 
  �������е������age2��ֵ:getAge2()
----------------before new----------------- 
  �������е�ʵ������str1��ֵ:��getString1()
  ִ�и����е� ʵ���顡���� 
  ִ�и���Ĺ��췽����ClassLoaderTestParent()

  �������е�ʵ������str2��ֵ:getString2()
  ִ�������е� ʵ���� 
  ִ������Ĺ��췽����ClassLoader()
----------------after new------------------ 

*/