import java.io.InputStream;
import java.io.PrintStream;
class TestStandardIo 
{
	public static void main(String[] args) throws Exception
	{
		
		InputStream standardInput=System.in ;
		 
		int i=standardInput.read();
		int j=standardInput.read();
		int k=standardInput.read();
		int l=standardInput.read();
		 
		PrintStream standardOutput=System.out;
		standardOutput.println( ""+i+" "+j+" "+k+" "+l );
		System.out.println("ÄãÊäÈëµÄ×Ö·ûÊÇ"+(char)i+" "+ (char)j+" "+(char)k+" "+(char)l);
	}
}
