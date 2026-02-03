package Bus;

public class Bus {
    private String DriverSurname; // ФИО водителя
    private int BusNumber; // Бортовой номер автобуса
    private int RouteNumber; // Номер маршрута
    private String Mark; // Марка автобуса
    private int YearStart; // Год начала эксплуатации
    private int Mileage; // Пробег

    public Bus() {
        DriverSurname = "No Driver";
        BusNumber = 0;
        RouteNumber = 0;
        Mark = "No bus";
        YearStart = 0;
        Mileage = 0;
    }

    public Bus(String valueDriverSurname, int valueBusNumber, int valueRouteNumber, String valueMark, int valueYearStart, int valueMileage) {
        DriverSurname = valueDriverSurname;
        BusNumber = valueBusNumber;
        RouteNumber = valueRouteNumber;
        Mark = valueMark;
        YearStart = valueYearStart;
        Mileage = valueMileage;
    }

    public String getDriverSurname() {
        return DriverSurname;
    }

    public void setDriverSurname(String driverSurname) {
        DriverSurname = driverSurname;
    }

    public int getBusNumber() {
        return BusNumber;
    }

    public void setBusNumber(int busNumber) {
        BusNumber = busNumber;
    }

    public int getRouteNumber() {
        return RouteNumber;
    }

    public void setRouteNumber(int routeNumber) {
        RouteNumber = routeNumber;
    }

    public String getMark() {
        return Mark;
    }

    public void setMark(String mark) {
        Mark = mark;
    }

    public int getYearStart() {
        return YearStart;
    }

    public void setYearStart(int yearStart) {
        YearStart = yearStart;
    }

    public int getMileage() {
        return Mileage;
    }

    public void setMileage(int mileage) {
        Mileage = mileage;
    }

    public void show() {
        System.out.println("<-------------------->" +
                "\nВодитель: " + DriverSurname +
                "\nБортовой номер автобуса: " + BusNumber +
                "\nНомер маршрута: " + RouteNumber +
                "\nМарка автобуса: " + Mark +
                "\nГод начала эксплуатации: " + YearStart +
                "\nПробег: " + Mileage +
                "\n<-------------------->");
    }

    public int checkRoute(int route, int count) {
        if (this.RouteNumber == route & count == 0) {
            System.out.print("Список автобусов, работающих по " + route + " маршруту:\n");
            this.show();
            count++;
        } else if (this.RouteNumber == route & count != 0) {
            this.show();
            count++;
        }
        return count;
    }

    public int checkYear(int count) {
        if (2025 - this.YearStart > 10 & count == 0) {
            System.out.print("Список автобусов, которые эксплуатируются более 10 лет:\n");
            this.show();
            count++;
        } else if (2025 - this.YearStart > 10 & count != 0) {
            this.show();
            count++;
        }
        return count;
    }

    public int checkMileage(int count) {
        if (this.Mileage > 10000 & count == 0) {
            System.out.print("Список автобусов с пробегом более 10000 км:\n");
            this.show();
            count++;
        } else if (this.Mileage > 10000 & count != 0) {
            this.show();
            count++;
        }
        return count;
    }
}