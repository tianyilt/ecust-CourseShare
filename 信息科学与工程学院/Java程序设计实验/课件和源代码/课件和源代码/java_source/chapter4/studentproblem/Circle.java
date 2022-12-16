public class Circle {
    private Point  centre ;
    private int radius;
    
	public Circle() {		
	}
	public Circle(Point centre2, int radius2) {		
		 Point centre = centre2;
		 int radius = radius2;
	}
	public Point getCentre() {		return centre;	}
	public void setCentre(Point centre) {		this.centre = centre;	}
	public int getRadius() {		return radius;	}
	public void setRadius(int radius) {		this.radius = radius;	}	
	
	public void printCircle(){
		System.out.println("x:"+centre.getX()+" y:"+centre.getY()+" radius:"+radius);
	}
}
