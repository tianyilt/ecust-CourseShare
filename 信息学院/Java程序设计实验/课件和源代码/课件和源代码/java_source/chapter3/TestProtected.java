class Card{
   protected  String name;
   String tel;
   Card(String cardName,String cardTel){
      name=cardName;tel=cardTel;
   }
   String  getName(){   return name;}
   String  getTel(){  return tel; }
}

public class  TestProtected{
    public static void main(String[] args){
    Card card=new Card("华东理工大学","57954734");
      System.out.println(card.getName()+" "+card.getTel());
      System.out.println(card.name+" "+card.tel);         
   }
}


