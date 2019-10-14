import java.io.*;
 import java.util.Calendar;
class  ListAllFiles
{
	public void dir(int level,String str ){
          //str:文件的绝对路径+文件名
		  //level:目录的层次

         File file=new File(str);
		 File file2=null;
		 String[] list=file.list();
		 for(int i=0;i<list.length;i++){
              
		   file2=new File(str+"/"+list[i]);
		     Long time =file.lastModified();        
			 Calendar cd = Calendar.getInstance();        
			 cd.setTimeInMillis(time);        
			   

		   if(file2.isFile()){ 
             //  System.out.println("时间："+cd.getTime()+" 文件名:"+list[i]+" 大小:"+file2.length()); 
		     //以下代码控制"-",以便显示更美观
			 String str2="";
			 for(int t=1;t<=level;t++){
				 str2+="-";
			 }
			 str2+=list[i] ;
			  System.out.println( "文件名:"+str2 ); 
		 
		   }
		   if(file2.isDirectory()){
                //System.out.println("时间："+cd.getTime()+"目录名:"+list[i]); 
				String str2="";
			    for(int t=1;t<=level;t++){
				 str2+="-";
			     }
			    str2+=list[i] ;
			      
				 System.out.println( "目录名:"+str2); 
			  
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
		all.dir(1,"d:/save/Library-ejb");
       // System.out.println(all.N(4));
	}
}
