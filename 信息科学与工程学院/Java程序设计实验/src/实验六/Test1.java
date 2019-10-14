package 实验六;

class Test1 {
    public static void main(String[] args) {
        // 动态绑定
        Parent person = new Parent();
        person.prnX();
        Child1 child1 = new Child1();
        child1.prnX();
        Child2 child2 = new Child2();
        child2.prnX();

        // 静态绑定
        person.prnXY();
        child1.prnXY();
        child2.prnXY();
    }
}

class Parent {
    public int x = 1, y = 2;

    public void prnXY() {
        System.out.println(" " + x + " " + y);
    }

    public void prnX() {
        System.out.println("Parent: " + x);
    }
}

class Child1 extends Parent {
    public int x = 3;

    public void prnX() {
        System.out.println("Child1: " + x);
    }
}

class Child2 extends Parent {
    public int x = 4;

    public void prnX() {
        System.out.println("Child1: " + x);
    }
}
