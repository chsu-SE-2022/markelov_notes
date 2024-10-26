from abc import ABC, abstractmethod

# Пользовательское исключение
class DeviceError(Exception):
    pass

# Абстрактный базовый класс для устройств передачи данных
class DataDevice(ABC):
    def __init__(self, name: str, capacity: int): # конструктор
        self._name = name # имя устройства
        self._capacity = capacity # пропускная способность

    @property
    def name(self):
        return self._name # Геттер для name

    @name.setter # Сеттер для name
    def name(self, value):
        self._name = value

    @property
    def capacity(self):
        return self._capacity # Геттер для capacity

    @capacity.setter # Сеттер для capacity
    def capacity(self, value):
        # Проверка на положительное значение
        if value > 0:
            self._capacity = value
        else:
            raise ValueError("Пропускная способность должна быть положительной")

    # Абстрактный метод (должен быть реализован в подклассах)
    @abstractmethod
    def transmit(self):
        pass

    # Статический метод
    @staticmethod
    def info():
        return "Это устройство используется для передачи данных"

# Класс WiFi-роутера, наследующий DataDevice
class WiFiRouter(DataDevice):
    def __init__(self, name: str, capacity: int, frequency: float):
        super().__init__(name, capacity)
        self.frequency = frequency # дополнительное поле для частоты сигнала

    # Переопределение метода передачи данных
    def transmit(self):
        return f"через Wi-Fi на частоте {self.frequency} ГГц."

    # Перегрузка оператора сложения для роутеров
    def __add__(self, other):
        if isinstance(other, WiFiRouter):
            return WiFiRouter(f"Объединенный роутер {self.name} и {other.name}", self.capacity + other.capacity, (self.frequency + other.frequency) / 2)
        raise TypeError("Можно складывать только с другими объектами класса WiFiRouter")

# Класс мобильной антенны, наследующий DataDevice
class MobileAntenna(DataDevice):
    def __init__(self, name: str, capacity: int, radius: float):
        super().__init__(name, capacity)
        self.radius = radius # дополнительное поле для радиуса действия

    # Переопределение метода передачи данных
    def transmit(self):
        return f"через мобильную антенну с радиусом действия {self.radius} км."

# Композиция: Владелец устройств передачи данных
class DataOwner:
    def __init__(self, name: str, device: DataDevice):
        self.name = name
        self.device = device  # Агрегация
        self.a = DataDevice("имя", 15.0) # Композиция

    def introduce_device(self):
        return f"Мое устройство - {self.device.name}, пропускная способность {self.device.capacity} Мбит/с."

# Пример использования классов
try:
    router = WiFiRouter("Asus RT-AC68U", 1200, 5.0)
    antenna = MobileAntenna("Huawei BTS3900", 500, 20.0)
    owner = DataOwner("Анна", router)
    
    # Проверка предположения
    assert router.capacity > 0, "Пропускная способность роутера должна быть положительной."

    print(owner.introduce_device())   # Владелец представляет своё устройство

    # Использование статического метода
    print(DataDevice.info()) 

    # Перегрузка оператора сложения
    combined_router = router + WiFiRouter("TP-Link Archer C7", 1750, 2.4)
    print(f"Имя объединенного устройства: {combined_router.name}, общая пропускная способность: {combined_router.capacity} Мбит/с")

    # Полиморфизм
    devices = [router, antenna]
    for device in devices:
        print(f"{device.name} передает данные {device.transmit()}")

    # Пример использования исключений
    # Установим пропускную способность в отрицательное значение
    try:
        router.capacity = -500  # Это вызовет исключение
    except ValueError as e:
        print(f"Ошибка: {e}")

except AssertionError as ae:
    print(f"Ошибка утверждения: {ae}")
except DeviceError as de:
    print(f"Ошибка устройства: {de}")
except Exception as e:
    print(f"Произошла непредвиденная ошибка: {e}")
finally:
    print("Завершение работы программы.")

# Использование пользовательского исключения
try:
    raise DeviceError("Ошибка в работе устройства.")
except DeviceError as de:
    print(f"Обработка пользовательского исключения: {de}")
