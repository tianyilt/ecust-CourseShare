 

public class ArrayTest
{
	public void SetArray(int[] array){
		  for (int  i=0;i<=array.length-1 ;i++ )
		  {
			    array[i]=1;
		  }
	}
	public void ChangeArray(int[] array){
		  for (int  i=0;i<=array.length-1 ;i++ )
		  {
			    array[i]++;
		  }
	}
	public void PrintArray(int[] array){
		  for (int  i=0;i<=array.length-1 ;i++ )
		  {
			    System.out.print(" "+array[i]);
		  }
		  System.out.println( );
	}

	public static void main(String[] args){
		int age[]=new int[10];
		  ArrayTest  arraytest1=new ArrayTest();
          arraytest1.SetArray(age);
		  arraytest1.PrintArray(age);
		 
		  arraytest1.ChangeArray(age);
		  arraytest1.PrintArray(age);

	}

};
