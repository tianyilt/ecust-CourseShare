import java.io.*;
public class TestReadObject{
  public static void main(String[] args){
   try{
      Employee Tom=null;       
      FileInputStream TomFile=new FileInputStream("d:/save/EmployeeObject.dat");
      ObjectInputStream in=new ObjectInputStream(TomFile);
      Tom=(Employee)in.readObject();
      System.out.println(Tom.toString());
      TomFile.close();
      in.close();
    }catch(Exception e){
      System.out.println("error "+e);
    }
 }
}
    