 interface Parent1{
   int a=1;
   void A();
 }

 interface Parent2{
   int b=2;
   void B();
 }
 
 interface Parent3{
   int c=3;
   void C();
 }

 public interface  TestMultiExtends extends Parent1,Parent2,Parent3{

  }