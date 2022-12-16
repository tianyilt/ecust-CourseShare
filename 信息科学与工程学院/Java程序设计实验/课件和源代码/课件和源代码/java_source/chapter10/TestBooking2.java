class Tickets{
   private int total;
   public Tickets(int total){ this.total=total;   }
   public void setTotal(int total){     this.total=total;   }
   public int getTotal( ){     return total;   }
}
class Booking implements Runnable{
	private Tickets tickets=null;
	public Booking( ){ 		}
	public void setTickets(Tickets tickets){          this.tickets=tickets;	}
	public Tickets getTickets(){		return tickets;	}
	public synchronized void   buy(){
		  int total=tickets.getTotal(); 
		  try{
			    System.out.println(Thread.currentThread().getName()+" is running... " );
		       Thread.sleep(300);
		     }catch(Exception e){
		       }
		  tickets.setTotal(total-1);
	}
	public void run(){
		 
		synchronized(tickets){
		  int total=tickets.getTotal(); 
		  try{
			    System.out.println(Thread.currentThread().getName()+" is running... " );
		       Thread.sleep(300);
		     }catch(Exception e){
                 System.out.println( " error " );
		       }
		  tickets.setTotal(total-1);
		} 
		 
		//buy();
	}
}
public class  TestBooking2{
	public static void main(String[] args)	{	   
	   Booking booking=new Booking( );
       Tickets tickets=new Tickets(100);
	   booking.setTickets(tickets); 
       Thread thread1=new Thread(booking,"thread1");
	   thread1.start();
	   Thread thread2=new Thread(booking,"thread2");
	   thread2.start();

	   try{
		   thread1.join();
		   thread2.join();
	   }catch(Exception e){
	   }
	   Tickets surplusTickets=booking.getTickets();
	   System.out.println(surplusTickets.getTotal());
	}
}
