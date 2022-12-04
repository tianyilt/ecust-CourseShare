import java.io.*;
 import java.util.Calendar;
class  SimpleListAllFiles
{
	public void dir(int level,String str ){
          //str:文件的绝对路径+文件名
		  //level:目录的层次

         File file=new File(str);
		 File file2=null;
		 String[] list=file.list();
		 for(int i=0;i<list.length;i++){
              
		   file2=new File(str+"/"+list[i]);
		     
		   if(file2.isFile()){ 
               System.out.println( "文件名:"+str+"/"+list[i] ); 
		   }
		   if(file2.isDirectory()){
                 
			      
				 System.out.println( "目录名:"+str+"/"+list[i]); 
			  
			    dir(level+1,str+"/"+list[i]);  //递归

			} 
		 } 
		 return ;
	}

	public  int N(int i){
		int result=1;
		if (i==1)
		{
              result=1;
		}
		if(i>1){
			result=i*N(i-1);
		}
		return result;
	}


	public static void main(String[] args) 
	{
		ListAllFiles all=new ListAllFiles();
		//all.prn("d:\\save");
		all.dir(1,"d:/save/file");
       // System.out.println(all.N(4));
	}
}
