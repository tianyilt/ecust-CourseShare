//file name:Fibonacci.java
public class Fibonacci{
  public static  void main(String[] args){
     int[]  fib=new int[30];
     Fib_value(fib);
     Display_Fib(fib);
  }
  
  public static void Fib_value(int[] fib){
     fib[0]=0;
     fib[1]=1;
     for(int i=2;i<30;i++){
        fib[i]=fib[i-2]+fib[i-1];
     }
   }

  public static void Display_Fib(int[] fib){
     for(int i=0;i<30;i++){
        System.out.println(fib[i]);
     }
  }
}



