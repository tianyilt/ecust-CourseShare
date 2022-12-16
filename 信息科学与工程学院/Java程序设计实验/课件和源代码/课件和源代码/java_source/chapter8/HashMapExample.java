import java.util.Set;  
import java.util.Map; 
import java.util.HashMap; 
import java.util.Iterator; 
public class HashMapExample { 
    public static void main( String[] args ){ 
        // Create a new HashMap 
        Map map = new HashMap(); 

        // Add Items to the HashMap 
        map.put( new Integer( 1 ), "One" ); 
        map.put( new Integer( 2 ), "Two" ); 
    map.put( new Integer( 5 ), "F3ive" );  
        map.put( new Integer( 3 ), "Three" ); 
        map.put( new Integer( 4 ), "Four" ); 
        map.put( new Integer( 5 ), "Fiv5e" );          
 
        // Use iterator to display the keys and associated values 
        System.out.println( "Map Values Before: " ); 
        Set keys = map.keySet(); 
        for( Iterator i=keys.iterator(); i.hasNext(); ){ 
            Integer key = ( Integer )i.next(); 
            String value = ( String )map.get( key ); 
            System.out.println( key + " = " + value ); 
        } 

        // Remove the entry with key 3 
        System.out.println( "\nRemove element with key 3" ); 
        map.remove( new Integer( 3 ) ); 

        // Use iterator to display the keys and associated values 
        System.out.println( "\nMap Values After: " ); 
        keys = map.keySet(); 
        for( Iterator i=keys.iterator(); i.hasNext(); ){ 
            Integer key = ( Integer )i.next(); 
            String value = ( String )map.get( key ); 
            System.out.println( key + " = " + value );  
        } 
    } 
} 
