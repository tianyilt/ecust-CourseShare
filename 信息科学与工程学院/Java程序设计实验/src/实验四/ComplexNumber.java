package 实验四;

public class ComplexNumber {
    private int real = 0, image = 0;

    public void set(int a, int b) {
        this.real = a;
        this.image = b;
    }

    public void set_real(int a) {
        this.real = a;
    }

    public void set_image(int b) {
        this.image = b;
    }

    public String get() {
        if (this.image != 0) {
            if (this.real != 0) return this.real + "+" + this.image + "i";
            else return this.image + "i";
        } else return String.valueOf(this.real);
    }

    public String get_real() {
        return String.valueOf(this.real);
    }

    public String get_image() {
        return this.image + "i";
    }

    public ComplexNumber add(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber();
        result.set(this.real + num.real, this.image + num.image);
        return result;
    }

    public ComplexNumber sub(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber();
        result.set(this.real - num.real, this.image - num.image);
        return result;
    }

    public ComplexNumber mul(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber();
        result.set(this.real * num.real - this.image * num.image,
                   this.image * num.image - this.image * num.real);
        return result;
    }
}
