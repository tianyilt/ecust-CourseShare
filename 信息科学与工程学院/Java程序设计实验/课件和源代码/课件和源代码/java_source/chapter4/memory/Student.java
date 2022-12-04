 
public class  Student extends Person    //学生类
{ 
	private String major;  //专业
	private int score  ;    //高考成绩

	public Student(){} 
	public Student(int No,String name,String sex,String major, int score ){
	  // super( No, name, sex);
	   setNo(No);setName(name);setSex(sex); 
       this.major=major;   this.score=score; 
	}
    public void setMajor(String major){ this.major=major;}
	public String getMajor(){ return major;} 

	 

	public void setScore(int score){this.score=score;}
	public int getScore(){return this.score;}
	 
	public void speak(){  
	   System.out.println("学生: "+"  学校:"+school+"    编号:"+getNo()+"    姓名:"+getName()+"    性别:"+getSex()+" 所在专业:"+getMajor()+ " 高考成绩:"+getScore() );
	}
}
