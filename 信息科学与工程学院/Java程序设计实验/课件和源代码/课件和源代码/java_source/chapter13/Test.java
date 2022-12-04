class  Code
{
	 public synchronized void prn1(int str){
		 System.out.println(Thread.currentThread().getName()+" "+str);
		 try{
			 Thread.sleep(1000);
			 System.out.println(Thread.currentThread().getName() +" "+str+"sleep end");
		 }catch(InterruptedException e){
		 }
	 }
	 public synchronized void prn2(int str){
		 System.out.println(Thread.currentThread().getName()+" "+str);
		 try{
			 //Thread.sleep(1000);
			 Thread.sleep(200);
			 System.out.println(Thread.currentThread().getName() +" "+str+"sleep end");
		 }catch(InterruptedException e){
		 }
	 }
	 public  void prn3(int str){

		  System.out.println(Thread.currentThread().getName()+" "+str);
        try{
			 Thread.sleep(200);
			 System.out.println(Thread.currentThread().getName() +" "+str+"sleep end");
		 }catch(InterruptedException e){
		 }
	 }
}

class R1 implements Runnable{
	Code code;
	public R1(Code code){
		this.code=code;
	}
	public void run(){
		for(int i=0;i<=3;i++){
			code.prn1(i);
		}	
	}
}
class R2 implements Runnable{
	Code code;
	public R2(Code code){
		this.code=code;
	}
	public void run(){
		for(int i=0;i<=3;i++){
			code.prn2(i);
		}	
	}
}
class R3 implements Runnable{
	Code code;
	public R3(Code code){
		this.code=code;
	}
	public void run(){
		for(int i=0;i<=3;i++){
			code.prn3(i);
		}	
	}
}
public class Test{

  public static void main(String[] args){
	 Code code=new Code();
     R1 r1=new R1(code);
	 R2 r2=new R2(code);	  
     Thread t1=new Thread(r1);
	 t1.setName("t1");
	 Thread t2=new Thread(r2);
     t2.setName("t2");	  
	 t1.start();
	 t2.start();  

    
    try{
		 t1.join();
		 t2.join();
          
	 }catch(Exception e){
	 }

 System.out.println(".............");
	 R1 r11=new R1(code);	 
	 R3 r3=new R3(code);
     Thread t11=new Thread(r11);
	 t11.setName("t11");	 
	 Thread t3=new Thread(r3);
     t3.setName("t3");
     t11.start();
	 t3.start();

	 
  }
}