import java.io.*;
public class TestDataInputStream{
    public static void main(String[] args){ 
		int[] out={11,22,33,44,55,66};
	  try{	
		File file=new File("d:/save/TestDataOutInputStream.txt"); 

		FileOutputStream outputFile=new        
                        FileOutputStream(file);
		DataOutputStream dataOutputStream=new                                                                       
                        DataOutputStream(outputFile);         
		 for(int i=0;i<out.length;i++){
			 dataOutputStream.writeInt(out[i]); 
			 
		  }
         
        dataOutputStream.close();

        File file2=new File("d:/save/TestDataOutInputStream.txt"); 

		FileInputStream inputFile=new        
                        FileInputStream(file2);
		DataInputStream dataInputStream=new                                                                       
                        DataInputStream(inputFile);  
		   /*
		 for(int i=0;i<in.length;i++){
			in[i]=dataInputStream.readInt(); 
			System.out.println(in[i]);
		  }
		  */
		  
		  
		 int k=0; 
         while((dataInputStream.available())!=0){ //输入流中还有未读的数据
			 k=dataInputStream.readInt(); 
			 System.out.println(k); 
		 }

         dataInputStream.close();
		  
	   } catch(IOException e){ 
		   
		   e.printStackTrace();
		 }	    
    
	 }  
}
