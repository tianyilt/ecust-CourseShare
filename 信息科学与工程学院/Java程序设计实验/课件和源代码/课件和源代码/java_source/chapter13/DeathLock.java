class A{	 
	synchronized void prn( B b){
		System.out.println("A: prn(B b) begin ");
		try{
		 Thread.sleep(1000);
		}catch(Exception e){}
        b.prn2();
	    System.out.println("A: prn() end ");
	}
	synchronized void prn2(){
		System.out.println("A: prn2() begin ");
		try{
		 Thread.sleep(1000);
		}catch(Exception e){}
        System.out.println("A: prn2() end ");
	}
};
class B{	
	synchronized void prn(A a ){
		System.out.println("B: prn(A a) begin ");
		try{
		 Thread.sleep(1000);
		}catch(Exception e){}
        a.prn2();
		System.out.println("B: prn() end ");
	}
	synchronized void prn2(){
		System.out.println("B: prn2() begin ");
		try{
		 Thread.sleep(1000);
		}catch(Exception e){}
		System.out.println("B: prn2() end ");
	}
};
class R1 implements Runnable{
	A a;
	B b;
	public R1(A a,B b){		 
		this.a=a;
		this.b=b;		 
	}
	public void run(){
        a.prn(b);
	}
};
class R2 implements Runnable{
	A a;
	B b;
	public R2(A a,B b){
		this.a=a;
		this.b=b;
	}
	public void run(){
        b.prn(a);
	}
};
public class  DeathLock{
	public static void main(String[] args) {   
		A a=new A();
		B b=new B();			 
		 Runnable r1=new R1(a,b);		  
		 Runnable r2=new R2(a,b);		  
		 Thread t1=new Thread(r1);		  
		 Thread t2=new Thread(r2);		 
		 t1.start();
		 t2.start();
	}
}
