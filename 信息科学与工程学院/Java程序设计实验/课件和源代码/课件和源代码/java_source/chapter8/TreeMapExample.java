import java.util.Set;  
import java.util.Map; 
import java.util.TreeMap; 
import java.util.Iterator; 

public class TreeMapExample 
{ 
    public static void main( String[] args ){ 
        // Create a new TreeMap 
        Map map = new TreeMap(); 

        // Add Items to the TreeMap 
        map.put( new Integer( 1 ), "One" ); 
        map.put( new Integer( 2 ), "Two" ); 
		map.put( new Integer( 5 ), "Five4" );  
        map.put( new Integer( 3 ), "Three" ); 
        map.put( new Integer( 4 ), "Four" ); 
        map.put( new Integer( 5 ), "Five" );         

        // Use iterator to display the keys and associated values 
        System.out.println( "Map Values Before: " ); 
        Set keys = map.keySet(); 
        for( Iterator i=keys.iterator(); i.hasNext(); ){ 
            Integer key = ( Integer )i.next(); 
            String value = ( String )map.get( key ); 
            System.out.println( key + " = " + value ); 
        } 

        // Remove the entry with key 6 
        System.out.println( "\nRemove element with key 3" ); 
        map.remove( new Integer(3 ) ); 

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
