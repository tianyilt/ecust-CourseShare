class  ARunnable implements Runnable
{
	int i=0;
    public void run(){
	   System.out.println(" Thread1 begin ");   
	   for(int k=0;k<=i;k++){
          System.out.println("Thread1 is running: "+k);
	      try{
	       Thread.currentThread().sleep(1000);
		  }catch(Exception e){
            System.out.println("errror in thread1");
		  }
	   }
	   System.out.println(" Thread1 end ");   
	}
	public  ARunnable(int time){
		i=time;
	}
}

public class MainThreadTest2
{
	public static void main(String[] args){
	   System.out.println("main thread begin");   
       
	   Runnable ARunnable=new ARunnable(5);
	   Thread thread1=new Thread(ARunnable);	   
	   thread1.start();
        
		try{
			for(int i=0;i<=5;i++){
              System.out.println("main thread is running: "+i);     
			  Thread.sleep(2000);//Ò»ÃëÖÓ
			}
		  }catch(InterruptedException e){
             System.out.println("main thread interrupted");     
		   }	   
       System.out.println("main thread end");   
	}
};