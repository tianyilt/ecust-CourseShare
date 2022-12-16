import java.util.ArrayList; 
import java.util.Iterator; 
public class ArrayListExample {
  public static void main( String[] args ) { 
      ArrayList list = new ArrayList();
      list.add( new Integer( 1 ) );
      list.add( new Integer( 2 ) );
      list.add( new Integer( 3 ) ); 
      list.add( new Integer( 4 ) );
      list.add( new Integer( 5 ) ); 
     for( int i=0; i<list.size(); i++ ) { 
           Integer integer = ( Integer )list.get( i );          
           System.out.print( integer +"  ");
      } 
  System.out.println();
     list.remove( 2 ); 
     list.set(2 , new Integer( 33 ) ); 
     for( Iterator i=list.iterator(); i.hasNext(); ) { 
          Integer integer = ( Integer )i.next();       
          System.out.print( integer +"  "); 
       }
   } 
} 
