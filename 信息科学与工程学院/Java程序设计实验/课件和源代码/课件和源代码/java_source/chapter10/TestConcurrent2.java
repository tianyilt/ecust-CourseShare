class Print implements Runnable{ 	 
	public void run(){
		int i=0;
		do {
			i++;
		    System.out.print(" print "+i);
			Thread.sleep(2000);
		}while(true); 
	} 
}  
class Input implements Runnable{		 
	public void run(){
		int sum=0;
		int i=0;		
		do {
			 sum+=i;
		     i++;
		     System.out.print("  sum:"+sum);
			 Thread.sleep(2000);
		}while(true); 
	} 
}
public class TestConcurrent2 { 
	public static void main(String[] args) { 
		Print p=new Print();
		Input i=new Input(); 
		Thread t1=new Thread(p);
		Thread t2=new Thread(i);
		t1.start();
		t2.start(); 
	} 
}

