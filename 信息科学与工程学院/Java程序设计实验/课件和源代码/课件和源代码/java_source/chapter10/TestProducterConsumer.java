class Food{
	private String name;
	public Food(String name){this.name=name;}
	public String getName(){return name;}
}
class Box{
	private int num;
	private Food[] foods;
	private int current;
	public Box(){}
	public Box( int num){ 
        this.num=num;
		foods=new Food[num];
		current=-1;
	}

	public  synchronized void put(Food food){ 
		System.out.println(Thread.currentThread().getName() +"  put... " );
		if(current< (num-1)){
		  current++;
		  System.out.println(Thread.currentThread().getName()+" put "+current +" apple"); 
          foods[current]=food; 
		  notify();   //该方法一定要放在同步方法或者同步块中，否则运行报错。
		    
		} else{
			try{
				System.out.println(Thread.currentThread().getName()+"  wait..."   );
			    wait();
             
			}catch(Exception e){
			}
			  
		 }	
	}
	public  synchronized Food get( ){
		System.out.println(Thread.currentThread().getName() +"  get... " );
		Food food=null;
		if(current>=0){ 
		   System.out.println(Thread.currentThread().getName()+" get "+current +" apple");  
           food=foods[current];
		   current--;
		   notify();   //该方法一定要放在同步方法或者同步块中，否则运行报错。
		   
		}else{
             try{
		      System.out.println(Thread.currentThread().getName() +"  wait..." );
			  wait();
              
			 }catch(Exception e){
			 }
			 
		 }		
		return food;
	}
}
class  Producter implements Runnable{
   private  Box box=null;
   public Producter(Box box){this.box=box;}

   public void run(){
       int i=0;
	   java.util.Random random = new java.util.Random(); 
	   int second=0;
       while(true){
		 
		 Food food=new Food(""+i +" apple");
         box.put(food); 
		 i++;

		  
		 try{
		    second=Math.abs(random.nextInt())%1000;
			System.out.println(Thread.currentThread().getName() +"  sleep... " +second);
			Thread.sleep(second);
                            
		   //Thread.sleep(1000);
		 }catch(Exception e){
		 }
		
	   }
   }	 
}

class Consumer implements Runnable{
   private  Box box=null;
   public Consumer(Box box){this.box=box;}
   
   public void run(){ 
	 java.util.Random random = new java.util.Random(); 
	 int second=0;
     while(true){

         Food food=null;
         food=box.get();  

		 try{
			  second=Math.abs(random.nextInt())%1000;
			  System.out.println(Thread.currentThread().getName() +"  sleep... " +second);
			  Thread.sleep(second);
                            
		   //Thread.sleep(1000);
		 }catch(Exception e){
		 }
	   } 
   }	
}

public class TestProducterConsumer{

	public static void main(String[] args)	{
		 

		Box myBox=new Box(4);  //notify(),notifyAll()恢复相同对象(myBox)中第一个调用wait()的线程。


		Producter p=new Producter(myBox);
		Consumer c=new Consumer(myBox);

		Thread  pt=new Thread(p,"Producter");
        Thread  ct=new Thread(c,"Consumer");

        pt.start();
		ct.start();
	}
}