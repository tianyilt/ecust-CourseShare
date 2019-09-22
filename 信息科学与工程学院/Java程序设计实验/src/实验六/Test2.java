package 实验六;

class Test2 {
	public static void main(String[] args) {
		Parent parent = new Child1();
		parent.prnX();
		parent.prnXY();
		parent = new Child2();
		parent.prnX();
		parent.prnXY();
	}
}

//class Parent {
//	public int x=1, y=2;
//	public void prnXY() {
//		System.out.println(" " + x + " " + y);
//	}
//	public void prnX() {
//		System.out.println("Parent: " + x);
//	}
//}
//
//class Child1 extends Parent{
//	public int x=3;
//	public void prnX() {
//		System.out.println("Child1: " + x);
//	}
//}
//
//class Child2 extends Parent{
//	public int x=4;
//	public void prnX() {
//		System.out.println("Child2: " + x);
//	}
//}
