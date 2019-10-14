 package PointPackage;

 public class Point{
   public int x,y;
   public void move(int dx,int dy){x+=dx;y+=dy;}
 }
  
 class Line{
  Point start,end; 
  public void setLine(Point p1,Point p2){
     start=p1;end=p2;
	}
 }
