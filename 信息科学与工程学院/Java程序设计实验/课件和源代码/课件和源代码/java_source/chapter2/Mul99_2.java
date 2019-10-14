public class Mul99_2
{
    public static void main(String args[])
    {
        int i,j,n=9;
        System.out.print("   *   |");
        for (i=1;i<=n;i++)
            System.out.print("   "+i);
        System.out.print("\n-------|");
        for (i=1;i<=n;i++)
            System.out.print("----");
        System.out.println();
        for (i=1;i<=n;i++)
        {
            System.out.print("   "+i+"   |");
            for (j=1;j<=i;j++)
	         System.out.print("  "+i*j);
            System.out.println();
        }
    } 
}
/*
   *   |  1   2   3   4   5   6   7   8   9
-------|------------------------------------
   1   |  1
   2   |  2   4
   3   |  3   6  9
   4   |  4   8  12  16
   5   |  5  10  15  20  25
   6   |  6  12  18  24  30  36
   7   |  7  14  21  28  35  42  49
   8   |  8  16  24  32  40  48  56  64
   9   |  9  18  27  36  45  54  63  72  81

*/
