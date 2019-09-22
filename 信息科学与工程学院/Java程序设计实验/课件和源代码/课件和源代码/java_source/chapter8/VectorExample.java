import java.util.Vector; 
import java.util.Iterator; 
public class VectorExample {
  public static void main( String[] args ) { 
      Vector vector = new Vector();
      vector.add( new Integer( 1 ) );
      vector.add( new Integer( 2 ) );
      vector.add( new Integer( 3 ) ); 
      vector.add( new Integer( 4 ) );
      vector.add( new Integer( 5 ) ); 
     for( int i=0; i<vector.size(); i++ ) { 
           Integer integer = ( Integer )vector.elementAt( i );          
           System.out.println( integer );
      } 
     vector.remove( 2 ); 
     vector.setElementAt( new Integer( 33 ), 2 ); 
     for( Iterator i=vector.iterator(); i.hasNext(); ) { 
          Integer integer = ( Integer )i.next();       
          System.out.println( integer ); 
       }
   } 
} 
