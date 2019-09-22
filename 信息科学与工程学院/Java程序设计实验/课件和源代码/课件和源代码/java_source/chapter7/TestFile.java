import java.io.*;
public class TestFile{
   public static void main(String[] args){   
	File file=new File("d:/save/TestFile.java");
	if (file.exists()){			     
             System.out.println(file.canRead()+" "+
                                            file.canWrite());
	      }else{
     		System.out.println("no exits!");
	      }
     }
}
