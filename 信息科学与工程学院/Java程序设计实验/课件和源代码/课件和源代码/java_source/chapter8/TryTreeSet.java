import java.util.*;
    public class TryTreeSet{
       public static void main(String[] args){
            Random Rvalue=new Random();
            TreeSet  set=new TreeSet();
            //HashSet   set=new HashSet();
			Integer data;
             for(int i=0;i<10;i++){
                  data=new Integer(Rvalue.nextInt()%10);
				  System.out.print(data+" ");
                  set.add(data);
             }
		 
            System.out.println("\n-------sorted---------");
             Iterator  it=set.iterator();
             while(it.hasNext()){
                 System.out.print(it.next()+" ");
              }
     }
	}