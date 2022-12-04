//¾Å¾Å³Ë·¨±í

public class Mul99
{
    public static void main(String args[])
    {
        int i,j,n=9;
        System.out.println("*  1  2   3   4   5   6   7   8   9");
        for (i=1;i<=n;i++)
        {   System.out.print( i);
            for (j=1;j<=i;j++)
                System.out.print("  "+i*j);
            System.out.println();
        }
    } 
}