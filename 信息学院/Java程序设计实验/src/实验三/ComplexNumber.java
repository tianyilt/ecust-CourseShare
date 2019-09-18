package 实验三;

public class ComplexNumber {
    int real = 0, image = 0;

    String get() {
        if (this.image != 0) {
            if (this.real != 0) return this.real + "+" + this.image + "i";
            else return this.image + "i";
        } else return String.valueOf(this.real);
    }

    String get_real() {
        return String.valueOf(this.real);
    }

    String get_image() {
        return this.image + "i";
    }

    ComplexNumber add(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber(){{
            real=this.real + num.real; image= this.image + num.image;}};
        return result;
    }

    ComplexNumber sub(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber(){{
            real=this.real - num.real; image= this.image - num.image;}};
        return result;
    }

    ComplexNumber mul(ComplexNumber num) {
        ComplexNumber result = new ComplexNumber(){{
            real=this.real * num.real - this.image * num.image;
            image= this.image * num.image - this.image * num.real;}};
        return result;
    }
}
