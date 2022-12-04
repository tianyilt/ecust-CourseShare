class MainThreadTest
{
	public static void main(String[] args) 
	{
		Thread t=Thread.currentThread();	//通过currentThread()方法获得主线程
		System.out.println("current Thread: "+t.getName());
		t.setName("zhang");    //改变线程的名字       
        System.out.println("after name changed: "+t.getName());
		try{
			for(int i=0;i<=5;i++){
              System.out.println(i);     
			  Thread.sleep(1000);//一秒钟
			}
		  }catch(InterruptedException e){
             System.out.println("main thread interrupted");     
		   }
	}
}
