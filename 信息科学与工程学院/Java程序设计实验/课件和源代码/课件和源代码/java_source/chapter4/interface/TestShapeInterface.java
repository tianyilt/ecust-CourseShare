interface Shape{
	  double area(); //求面积
	  double permeter();  //周长 
}
class Circle implements Shape {
	private double radius;
	public Circle(double radius){this.radius=radius;}
    public double area()  { return 3.1415926*radius*radius;}  
	public double permeter()  { return 2*3.1415926*radius ;} 
}

class Rectangle implements Shape {
	private double length ,width ;
	public Rectangle(double length, double width){
		this.length=length; this.width=width;
	}
    public double area()  { return length*width;} 
	public double permeter()  { return 2*(length+width) ;} 
}

public class TestShapeInterface{ 
   public static void main(String[] args) 
	{
		 Shape shape=null;
		 Circle circle=new Circle(2.0);
		 Rectangle rectangle=new Rectangle(2.0,3.0);
		 shape=circle;
		 System.out.println( shape.area());
		 shape=rectangle;
		 System.out.println( shape.area());
	}

}