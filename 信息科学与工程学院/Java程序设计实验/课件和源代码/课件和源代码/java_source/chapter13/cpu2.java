class SynStack{
	int[] stack=new int[5];
	int point=0;
	public synchronized void push(int i){	
		if(point<=4){
			notify();
		stack[point]=i;
		point++;
		return;
		}else{
			try{
				wait();
				}catch(Exception e){
			   }
		}
	}
	public synchronized int pop(){
		if(point>=1){
			notify();
		    point--;
		 return stack[point];
		}else{
			try{
				wait();
				}catch(Exception e){
			   }
			return -1;
		}
	}

};


class Producer implements Runnable{
   SynStack synstack;
   public   Producer(SynStack synstack){
	   this.synstack=synstack;
   }
   public void run(){
	   int i=0;
	   while(true){
		   synstack.push(i);
		   System.out.println("point: "+(synstack.point-1)+"  producer: "+i);
		   i++;
		   try{
		     Thread.sleep(100);
	       }catch(Exception e){
		   }
	   }
   }
};

class Consumer implements Runnable{
   SynStack synstack;
   public Consumer(SynStack synstack){
	   this.synstack=synstack;
   }
   public void run(){
	   int i=0;
	   while(true){
		   i=synstack.pop();
		     System.out.println("point: "+synstack.point+"  consumer: "+i);
		   try{
		     Thread.sleep(1000);
	       }catch(Exception e){
		   }
	   }
   }
};

public class  cpu2
{
	public static void main(String[] args) 
	{
		 SynStack synstack=new SynStack();
		 Runnable producer=new Producer(synstack); 
         Runnable consumer=new Consumer(synstack);
		 Thread producerThread=new Thread(producer);
		 Thread consumerThread=new Thread(consumer);
		 producerThread.start();
		 consumerThread.start();
	}
}
