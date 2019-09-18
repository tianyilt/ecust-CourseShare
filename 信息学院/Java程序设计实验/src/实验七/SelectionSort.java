package 实验七;

import java.util.Random;

public class SelectionSort {
    public static void main(String[] args) {
        Random value = new Random();
        int[] a = new int[10];
        for (int i = 0; i < 10; i++) {
            a[i] = value.nextInt() % 100;
        }
        for (int i = 0; i < 10; i++) {
            int min = i;
            for (int j = i + 1; j < 10; j++) {
                if (a[min] > a[j]) {
                    min = j;
                }
            }
            if (min != i) {
                int temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }
            System.out.print("第" + (i + 1) + "趟排序后");
            for (int k = 0; k < 10; k++) {
                System.out.print(a[k] + " ");
            }
            System.out.print("\n");
        }
    }
}
