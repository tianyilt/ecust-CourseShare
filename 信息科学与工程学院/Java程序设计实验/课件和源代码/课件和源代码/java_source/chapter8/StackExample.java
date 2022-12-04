import java.util.Stack;  
public class StackExample 
{ 
    public static void main( String[] args ) 
    { 
        // Create a new LinkedList 
        Stack stack = new Stack(); 
        // Add Items to the array list 
        stack.push( new Integer( 1 ) ); 
        stack.push( new Integer( 2 ) ); 
        stack.push( new Integer( 3 ) ); 
        stack.push( new Integer( 4 ) ); 
        stack.push( new Integer( 5 ) ); 
        // Pop everything out of the stack and display the values  
        while( !stack.empty() ) 
        { 
            Integer element = ( Integer )stack.pop(); 
            System.out.print(  element +"  "); 
        } 
    } 
} 
