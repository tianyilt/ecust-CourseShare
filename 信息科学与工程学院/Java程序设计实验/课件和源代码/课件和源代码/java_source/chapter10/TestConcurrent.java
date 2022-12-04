class Print{ 
	public Print(){
		int i=0;
		do {
			i++;
		    System.out.print(" print "+i);
		}while(true);
	} 
} 
class Input{ 
	public Input(){
		int sum=0;
		int i=0; 
		do {
			 sum+=i;
		     i++;
		     System.out.print("  sum:"+sum);
		}while(true);
	} 
}
 
public class TestConcurrent { 
	public static void main(String[] args) {
		  Print p=new Print();
		  Input i=new Input(); 
          
		  //Input i=new Input(); 
		  //Print p=new Print(); 
	} 
}

