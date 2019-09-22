class SynStack{
	int[] stack=new int[6];
	int index=0;
	public void push(int i){	
		if(index<=5){
		stack[index]=i;
		System.out.println("index: "+index+"  producer: "+i);
		index++;
		return;
		}
	}
	public int pop(){
		if(index>=1){
		 index--;
		 System.out.println("index: "+index+"  consumer: "+stack[index]);
		 return stack[index];
		}else{
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
		  
		   i++;
		   try{
		     Thread.sleep(1000);
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
		    
		   try{
		     Thread.sleep(10000);
	       }catch(Exception e){
		   }
	   }
   }
};

public class  cpu3
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
