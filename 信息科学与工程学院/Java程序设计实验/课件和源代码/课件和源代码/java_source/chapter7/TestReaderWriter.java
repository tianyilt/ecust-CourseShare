import java.io.*;
public class TestReaderWriter{
  public static void main(String[] args){
    try{
      FileWriter fw=new FileWriter("d:/save/hello.txt");
      BufferedWriter bw=new BufferedWriter(fw);
      for(int i=0;i<10;i++){
        bw.write('a'+i);
       }
      bw.close();
      }catch(IOException e){
        System.out.println("error writer");
     }
    try{
      FileReader fr=new FileReader("d:/save/hello.txt");
      BufferedReader br=new BufferedReader(fr);
      for(int i=0;i<10;i++){
         System.out.println((char)br.read());
       }
      br.close();
    }catch(IOException e){
      System.out.println("error reader");
    }
   }
 }