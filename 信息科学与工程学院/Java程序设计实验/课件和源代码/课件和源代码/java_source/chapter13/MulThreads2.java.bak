class  Thread3 extends Thread
{
	public static int i=0;
	String kk="";
    public void run(){
	  while(true){
       System.out.println( kk+" "+i);
	   i++;
	   try{
	       sleep(1000);
		  }catch(Exception e){
            System.out.println("errror in thread1");
		  }
	  }
	}
	public Thread3(String k){
		kk=k;
	}
}

class  Thread4 extends Thread
{
	int i=0;
    public void run(){
	  while(true){
       System.out.println("Thread2 is running"+i);
	   i++;
	   try{
	       sleep(1000);
		  }catch(Exception e){
            System.out.println("errror in thread1");
		  }
	  }
	}	 
}

public class MulThreads2
{
	public static void main(String[] args){
       Thread thread3=new Thread3("thread3");
	   Thread thread4=new Thread4();
	   thread3.start();
	   //thread2.start();
	   Thread thread5=new Thread3("thread5");
	   thread5.start();
	}
};