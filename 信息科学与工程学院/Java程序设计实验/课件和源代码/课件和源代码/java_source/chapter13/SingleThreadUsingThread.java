class  Thread1 extends Thread{
	int i=0;
    public void run(){
	   for(int k=0;k<=i;k++){
          System.out.println("Thread1 is running"+k);
	      try{
	       sleep(1000);
		  }catch(Exception e){
            System.out.println("errror in thread1");
		  }
	   }
	}
	public Thread1(int time){
		i=time;
	}
}
public class SingleThreadUsingThread
{
	public static void main(String[] args){
       Thread thread1=new Thread1(10);	    
	   thread1.start();
	   
	}
};