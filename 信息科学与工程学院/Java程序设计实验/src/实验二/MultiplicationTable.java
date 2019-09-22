package 实验二;

public class MultiplicationTable {
	public static void main(String[] args) {
		System.out.println("*  1  2  3  4  5  6  7  8  9");
		for (int m=0; m<9; m++) {
			System.out.print(m+1);
			for (int n=0; n<m+1; n++)
			{
				System.out.printf(" %2d", (n+1)*(m+1));
			}
			System.out.println();
		}
	}
}
