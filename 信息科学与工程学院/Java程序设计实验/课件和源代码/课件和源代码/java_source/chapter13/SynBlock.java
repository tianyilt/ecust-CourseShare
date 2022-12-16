class  Callme{
	   void call(String str){
		 System.out.print("["+str);
		 try{
			 Thread.sleep(1000);
		 }catch(InterruptedException e){
			 System.out.println("errror");
		 }
		 System.out.println("]");
	 }
}

class Caller implements Runnable{
	String str="";
	Callme target;
	
	public Caller(Callme c,String s){
         target=c;
		 str=s;		  
	}
	public void run(){
       synchronized(target){
		   	target.call(str);
	   }
	}
}

public class  SynBlock{
  public static void main(String[] args){
	System.out.println("begin of main()");
    Callme cm1=new Callme();
    
	Caller c1=new Caller(cm1,"c1");
    Caller c2=new Caller(cm1,"c2");
    Caller c3=new Caller(cm1,"c3");
	
	Thread t1=new Thread(c1);
	Thread t2=new Thread(c2);
	Thread t3=new Thread(c3);
	t1.start();
	t2.start();
	t3.start();	 
    try{
		  t1.join();
		 t2.join();
		  t3.join();
	}catch(InterruptedException e){
		System.out.println("dddddddd");
	}
	 
	System.out.println("end of main()");
  }
}
/*
begin of main()
[c1]
[c2]
[c3]
end of main()
*/