import java.io.*; 
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Calendar;

public class  TestIo1{ 
	 
	//在d:/save目录下创建a,b子目录
	//在d:/save/a目录下创建c子目录
	public static void createDirectory() throws Exception{  
		String directory="d:/save";
		String aDirectory="d:/save/a";
		String bDirectory="d:/save/b";
		String cDirectory="d:/save/a/c";
		File a=new File(aDirectory);
		File b=new File(bDirectory);
		File c=new File(cDirectory);
		a.mkdir();
		b.mkdir();
		c.mkdir(); 
	} 
    public static void createFile() throws Exception{  
         String file="d:/save/a/ecust.txt";
		 File ecust=new File(file);
		ecust.createNewFile(); 
	} 
     
  //递归方式显示directory目录下所有的文件和子目录
	public static void dir(int level ,String directory){ 
        //directory:文件的绝对路径+文件名
	    //level:目录的层次

         File file=new File(directory);
		 File file2=null;
		 String[] list=file.list();
		 for(int i=0;i<list.length;i++){ 
		   file2=new File(directory+"/"+list[i]); 
		   if(file2.isFile()){ 
              //以下代码控制"-",以便显示更美观
			 String filename="";
			 for(int t=1;t<=level;t++){
				 filename+="-";
			 }
			 filename+=list[i] ;
			  System.out.println( "文件名:"+filename );  
		   }
		   if(file2.isDirectory()){
                //System.out.println("时间："+cd.getTime()+"目录名:"+list[i]); 
				String directory2="";
			    for(int t=1;t<=level;t++){
				     directory2+="-";
			    }
			    directory2+=list[i] ; 
				System.out.println( "目录名:"+directory2); 

			    dir(level+1,directory +"/"+list[i]);  //递归 
			} 
		 } 
		 return ;

	}
	public static void main(String[] args)  throws Exception
	{ 
		   
		 TestIo1.createDirectory();
		 TestIo1.createFile();
		  
		 TestIo1.dir(1,"d:/save/a"); 
	}
}
