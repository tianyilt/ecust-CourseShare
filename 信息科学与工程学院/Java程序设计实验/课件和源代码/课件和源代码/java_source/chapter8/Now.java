import java.util.*;
import java.text.*;
public class Now { 
   public static void main(String[] args) { 
      Date now = new Date(); 
      long nowLong = now.getTime(); 
      System.out.println("Value is " + nowLong); 
	  Date now1=new Date(nowLong);
      System.out.println( ""+now1.getYear()+"年" +now1.getMonth()+"月"+now1.getDate()+"日"+" 星期"+now1.getDay()); 


	  Date d1=new Date();
      System.out.println( ""+d1.getYear()+"年" +d1.getMonth()+"月"+d1.getDate()+"日"+" 星期"+d1.getDay()); 

	  

	  Date d2=new Date(0);
	  System.out.println( ""+d2.getYear()+"年" +d2.getMonth()+"月"+d2.getDate()+"日"+" 星期"+d2.getDay()); 

	  Date d3=new Date(2005-1900,5-1,12);
       System.out.println( ""+d3.getYear()+"年" +d3.getMonth()+"月"+d3.getDate()+"日"+" 星期"+d3.getDay()); 

	   Date now2 = new Date(); 
      DateFormat df2 = DateFormat.getDateInstance(); 
      String s2 = df2.format(now2); 
      System.out.println(" default: " + s2); 


      Date now3 = new Date(); 
      DateFormat df3 = DateFormat.getDateInstance(DateFormat.FULL,Locale.US); 
      String s3 = df3.format(now3); 
      System.out.println("US FULL:" + s3); 
	   
      Date now4 = new Date(); 
      DateFormat df4 = DateFormat.getDateInstance(DateFormat.FULL,Locale.UK); 
      String s4 = df4.format(now4); 
      System.out.println("UK FULL: " + s4); 
   
     Date now5 = new Date(); 
      DateFormat df5 = DateFormat.getDateInstance(DateFormat.SHORT,Locale.UK); 
      String s5 = df5.format(now5); 
      System.out.println("UK SHORT:" + s5);
   } 
} 


