
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.Random;
import java.io.RandomAccessFile;


//外部排序:在外存进行排序.
//数据保存在外存，排序的过程中，只读入需要待排的数据和需要比较的数据，而其它数据不读入到内存。
//每次排序的时候，只读两个int数据
public class  DiskSort
{
	//随机产生10个整数，保存到文件d:/save/data.dat中
	public static void saveData() throws Exception{

        File file=new File("d:/save/data.dat");
		file.createNewFile();
		int randomInt=0;
		int[] data=new int[10];//随机产生10个整数 
		Random random=new Random();
		for(int i=0;i<data.length;i++){ 
          randomInt=random.nextInt()%100;
		  data[i]=randomInt; 
		} 
        FileOutputStream fileoutput=new FileOutputStream(file);
        DataOutputStream output=new DataOutputStream(fileoutput);
		for(int i=0;i<data.length;i++){ 
		   output.writeInt(data[i]);// 将10个整数保存到文件d:/save/data.dat中
		} 
		output.close(); 
	}

    // 打印文件d:/save/data.dat中的数据
	public static void printData() throws Exception{

        File file=new File("d:/save/data.dat"); 
		long fileSize=file.length();
		int[] data=new int[(int)fileSize/4];
		 
        FileInputStream fileInput=new FileInputStream(file);
        DataInputStream input=new DataInputStream(fileInput);
		for(int i=0;i<data.length;i++){ 
		   data[i]=input.readInt();
		}
		for(int i=0;i<data.length;i++){ 
          System.out.print(data[i]);System.out.print(" ");
		}
		System.out.println( );
		input.close();

	}


    // 对文件d:/save/data.dat中的数据进行外部排序
	public static void sortData() throws Exception{

        File file=new File("d:/save/data.dat"); 
		long fileSize=file.length();
		int[] data=new int[(int)fileSize/4];
		 
        //FileInputStream fileInput=new FileInputStream(file);
        //DataInputStream input=new DataInputStream(fileInput);
		RandomAccessFile random=new RandomAccessFile(file,"rw");
		 
		int currentInt=0;
		int nextInt=0;
		int tempInt=0;
		for(int i=0;i<data.length;i++){ 
		   random.seek(i*4);
		   currentInt=random.readInt();
		    
           for(int j=(i+1);j<data.length;j++){
               random.seek(j*4);
			   nextInt=random.readInt(); 

			   if(nextInt>currentInt){
                 tempInt=currentInt;
				 random.seek(i*4);
				 random.writeInt(nextInt);
				 random.seek(j*4);
				 random.writeInt(tempInt);  
                 currentInt=nextInt;
			   } 
		   }
		   
		    currentInt=0;
		    nextInt=0;  
		}
		 
		random.close();

	}
	public static void main(String[] args) throws Exception
	{
         
		 DiskSort.saveData();
		 System.out.println(" 排序前的数据");
		 printData();
		 

		 sortData();//外部排序
		 System.out.println(" 排序后的数据");
		 printData();
	}
}
