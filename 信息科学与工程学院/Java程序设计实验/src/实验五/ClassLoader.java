package 实验五;

public class ClassLoader {
    public static void main(String[] args) {
        ClassLoaderTest loader = new ClassLoaderTest();
        loader.getAge();
        loader.getString();
    }
}

class ClassLoaderTest {
    static {
        System.out.println("执行静态块  static block");
    }

    public static int age = getAge();
    public String str = getString();

    public ClassLoaderTest() {
        System.out.println("执行构造方法　ClassLoader()");
    }

    public static int getAge() {
        System.out.println("执行getAge()  给类变量age赋值");
        return 1;
    }

    public static String getString() {
        System.out.println("执行getString()  给实例变量str赋值");
        return "String";
    }

    {
        System.out.println("执行实例块　 block");
    }
}
