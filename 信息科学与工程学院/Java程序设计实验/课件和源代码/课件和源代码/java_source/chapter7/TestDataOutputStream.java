import java.io.*;
public class TestDataOutputStream{
     public static void main(String[] args){  
	  int[] info={97,98,99,100,101,102};
	  String[] str={"aa","bb","cc"};
            try{
		File file=new File("d:/save/TestDataOutput.txt");
		file.createNewFile();
		FileOutputStream outputFile=new    
                            FileOutputStream(file);
		DataOutputStream datastream=new   
                            DataOutputStream(outputFile);
		for(int i=0;i<info.length;i++){
			datastream.writeByte(info[i]); //写int的低位字节
		  }	
		  for(int i=0;i<info.length;i++){
			datastream.writeChar(info[i]); //写int的低两位字节
		  }	
		 for(int i=0;i<info.length;i++){
			datastream.writeInt(info[i]);//写int的4位字节
		  }		  
		  
         for(int i=0;i<str.length;i++){
			datastream.writeChars(str[i]);//写String 的每位字符
		  }
		 datastream.close();
	   } catch(IOException e){
			System.out.println(e);
		}	    
     }
}
