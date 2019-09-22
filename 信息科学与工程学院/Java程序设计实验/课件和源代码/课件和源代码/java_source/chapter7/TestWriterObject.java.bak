import java.io.*;
public class TestWriterObject{
  public static void main(String[] args){
   try{
      Employee Tom=new Employee("TOM",20);       
      FileOutputStream TomFile=new FileOutputStream("d:/save/EmployeeObject.dat");
      ObjectOutputStream out=new ObjectOutputStream(TomFile);
      out.writeObject(Tom);
      TomFile.close();
      out.close();
    }catch(IOException e){
      System.out.println("error "+e);
    }
 }
}
    