public class Receipt {
    int number;
    int date; // формат: ГГГГММДД
    float sum;

    public Receipt(int number, int date, float sum) {
        this.number = number;
        this.date = date;
        this.sum = sum;
    }

    public float getSum() {
        return sum;
    }

    @Override
    public String toString() {

        return "Квитанция №" + number + ", дата: " + date + " сумма: " + sum;
    }
}
