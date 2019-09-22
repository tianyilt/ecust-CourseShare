import java.io.*;
public class TestRandomAccessFile{
  public  static void main(String[] args){
     int num=0;
     RandomAccessFile raf=null;
     try{
       raf=new RandomAccessFile("d:/save/test.dat","rw");     
       raf.seek(0);
       for(int i=1;i<=10;i++){
         raf.writeInt(i);
        }
       raf.close();
       }catch(IOException e){
       
        System.out.println("err1"+e);
       }
   
     try{
       raf=new RandomAccessFile("d:/save/test.dat","rw");
       raf.seek(0);
       for(int i=1;i<=((int)raf.length()/4);i++){
         num=raf.readInt();
         System.out.println(num);
        }
       raf.close();
       }catch(IOException e){
       System.out.println("err2"+e);         
       }   
  }
}