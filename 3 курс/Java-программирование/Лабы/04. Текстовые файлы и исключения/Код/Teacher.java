package mypack;

public class Teacher {
    private String name; // фамилия
    private String subject; // предмет
    private int hours; // количество часов

    public Teacher(String name, String subject, int hours) {
        this.name = name.trim();
        this.subject = subject.trim();
        this.hours = hours;
    }

    public String getName() {
        return name;
    }

    public String getSubject() {
        return subject;
    }

    public int getHours() {
        return hours;
    }
}
