class Rectangle {
   public int length,width;
   public Rectangle(int length,int width){
	 this.length=length;	 this.width=width;
   }
   public int area()     { return length*width;      }
   public int permeter() { return 2*(length+width);  }
   public int getLength(){   return length;          }
   public int getWidth() {   return width;           }
 }
class Square {
   public int edge;
   public Square(int edge)      { this. edge= edge;         }
   public int area()     {  return edge*edge;        }
   public int permeter() {  return 4*edge;           }
   public int getEdge()  {  return edge;             }
 }
