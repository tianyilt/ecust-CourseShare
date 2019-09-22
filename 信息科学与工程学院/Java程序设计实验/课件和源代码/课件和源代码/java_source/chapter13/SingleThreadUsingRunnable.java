class  ARunnable implements Runnable
{
	int i=0;
    public void run(){
	   for(int k=0;k<=i;k++){
          System.out.println("Thread1 is running"+k);
	      try{
	       Thread.currentThread().sleep(1000);
		  }catch(Exception e){
            System.out.println("errror in thread1");
		  }
	   }
	}
	public  ARunnable(int time){
		i=time;
	}
}

public class SingleThreadUsingRunnable
{
	public static void main(String[] args){
	   
       Runnable ARunnable=new ARunnable(10);
	   Thread thread1=new Thread(ARunnable);	   
	   thread1.start();
	   
	}
};