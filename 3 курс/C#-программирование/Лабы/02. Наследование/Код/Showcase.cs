using BarcodeLibrary;
using DataDevices;
using System;

namespace Showcase
{
    public class Showcase
    {
        private static int currentId = 1; // Статическое поле для уникальных идентификаторов
        private int id; // Уникальный идентификатор витрины
        private readonly DataDevices.DataDevices[] devices; // Массив для хранения товаров
        private int capacity; // Вместимость витрины

        public int Id
        {
            get => id;
            set
            {
                if (value == id) return;
                id = value;
                UpdateBarcode();
            }
        }

        // Закрытый конструктор
        private Showcase(int id, int capacity)
        {
            this.id = id;
            this.capacity = capacity;
            devices = new DataDevices.DataDevices[capacity];
        }

        // Оператор неявного преобразования
        public static implicit operator Showcase(int capacity)
        {
            return new Showcase(currentId++, capacity);
        }

        private void UpdateBarcode(DataDevices.DataDevices device, int index)
        {
            if (device != null)
            {
                device.Barcode.Text = $"{device.Id} {id} {index}";
            }
        }

        private void UpdateBarcode()
        {
            for (int i = 0; i < capacity; i++)
            {
                UpdateBarcode(devices[i], i);
            }
        }

        // Индексатор для получения/установки товаров
        public DataDevices.DataDevices this[int index]
        {
            get
            {
                if (index >= 0 && index < capacity && devices[index] != null)
                {
                    var device = devices[index];
                    devices[index] = null; // Снимаем товар с витрины (удаляем из ячейки)
                    return device;
                }
                return null; // Ячейка пустая или индекс вне допустимого диапазона
            }
            set
            {
                if (index >= 0 && index < capacity)
                {
                    devices[index] = value;
                    if (value != null)
                    {
                        UpdateBarcode(value, index); // Обновляем штрихкод
                    }
                }
            }
        }

        // Метод для добавления товара в первую пустую ячейку
        public void AddDevice(DataDevices.DataDevices device)
        {
            for (int i = 0; i < capacity; i++)
            {
                if (devices[i] == null) // Найти первую пустую ячейку
                {
                    this[i] = device; // Используем индексатор
                    break;
                }
            }
        }

        // Метод для добавления товара в конкретную позицию
        public void AddDevice(DataDevices.DataDevices device, int index)
        {
            if (index >= 0 && index < capacity && devices[index] == null) // Проверка, что позиция свободна
            {
                this[index] = device; // Используем индексатор для добавления в указанную ячейку
            }
        }

        // Метод для удаления товара из первой заполненной позиции
        public void RemoveDevice()
        {
            for (int i = 0; i < capacity; i++)
            {
                if (devices[i] != null) // Находим первую заполненную ячейку
                {
                    this[i] = null; // Удаляем товар
                    break;
                }
            }
        }

        // Метод для удаления товара из конкретной позиции
        public void RemoveDevice(int index)
        {
            this[index] = null; // Удаляем товар
        }

        // Метод для замены товара
        public void ReplaceDevice(int index, DataDevices.DataDevices newDevice)
        {
            this[index] = newDevice;
        }

        // Метод для перестановки товаров на витрине
        public void SwapDevices(int index1, int index2)
        {
            (this[index1], this[index2]) = (this[index2], this[index1]);
        }

        // Метод для поиска товара по ID
        public int FindById(int deviceId)
        {
            for (int i = 0; i < capacity; i++)
            {
                if (devices[i]?.Id == deviceId)
                {
                    return i; // Возвращаем индекс
                }
            }
            return -1; // Товар не найден
        }

        // Метод для поиска товара по наименованию
        public int FindByName(string name)
        {
            for (int i = 0; i < capacity; i++)
            {
                if (devices[i]?.Name == name)
                {
                    return i; // Возвращаем индекс
                }
            }
            return -1; // Товар не найден
        }

        // Метод для сортировки по ID
        public void SortById()
        {
            Array.Sort(devices, (p1, p2) => (p1?.Id ?? int.MaxValue).CompareTo(p2?.Id ?? int.MaxValue));
            UpdateBarcode();
        }

        // Метод для сортировки по наименованию
        public void SortByName()
        {
            Array.Sort(devices, (p1, p2) => string.Compare(p1?.Name ?? "\uFFFF", p2?.Name ?? "\uFFFF", StringComparison.Ordinal));
            UpdateBarcode();
        }

        // Переопределение ToString для вывода информации
        public override string ToString()
        {
            var result = $"Витрина {id}:\n";
            for (int i = 0; i < capacity; i++)
            {
                result += devices[i]?.ToString() ?? $"Ячейка {i}: Пусто\n";
            }
            return result;
        }
    }
}
