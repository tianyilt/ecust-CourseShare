class Card{
   private  String name;
   String tel;
   Card(String cardName,String cardTel){
      name=cardName;tel=cardTel;
   }
   String  getName(){   return name;}
   String  getTel(){  return tel; }
}

public class  TestPrivate{
    public static void main(String[] args){
    Card card=new Card("华东理工大学","57954734");
      System.out.println(card.getName()+" "+card.getTel());
       //System.out.println(card.name); 语法出错,不能访问name  
      System.out.println(card.tel);
   }
}

