using BarcodeLibrary;
using DataDevice;
using System;

namespace Showcase
{
    public class Showcase<T> : IShowcase<T> where T : class, IDataDevice
    {
        private static int currentId = 1; // Статическое поле для уникальных идентификаторов
        private int id; // Уникальный идентификатор витрины
        private readonly T[] devices; // Массив для хранения товаров
        private int capacity; // Вместимость витрины

        // Делегат для сравнения товаров
        private delegate int CompareDevices<T>(T device1, T device2);

        // Делегат для проверки товара на соответствие условию
        private delegate bool DeviceCondition<T>(T device);

        // Добавляем событие в IShowcase<T>
        private Action<IShowcase<T>> idChanged;

        public int Id
        {
            get => id;
            set
            {
                if (value == id) return;
                id = value;
                idChanged?.Invoke(this); // Вызываем событие
            }
        }


        // Закрытый конструктор
        private Showcase(int id, int capacity)
        {
            this.id = id;
            this.capacity = capacity;
            devices = new T[capacity];
        }

        // Оператор неявного преобразования
        public static implicit operator Showcase<T>(int capacity)
        {
            return new Showcase<T>(currentId++, capacity);
        }

        private void UpdateBarcode()
        {
            for (int i = 0; i < capacity; i++)
            {
                devices[i].UpdateBarcode(this, i);
            }
        }

        // Индексатор для получения/установки товаров
        public T this[int index]
        {
            get
            {
                if (index >= 0 && index < capacity)
                {
                    return devices[index];
                }
                return null;
            }
            set
            {
                if (index >= 0 && index < capacity)
                {
                    if (devices[index] != null) // Отписываем старое устройство
                    {
                        devices[index].IdChanged -= Device_IdChanged;
                    }
                    devices[index] = value; // Устанавливаем новое устройство
                    if (value != null)
                    {
                        value.IdChanged += Device_IdChanged;
                        idChanged += value.UpdateBarcode;
                        value.UpdateBarcode(this, index);
                    }
                }
            }
        }

        // Метод для добавления товара в первую пустую ячейку
        public void AddDevice(T device)
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
        public void AddDevice(T device, int index)
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
            if (index >= 0 && index < capacity)
            {
                if (devices[index] != null)
                {
                    devices[index].IdChanged -= Device_IdChanged; // Отписываемся от события
                }
                this[index] = null; // Удаляем товар

            }
        }

        // Метод для замены товара
        public void ReplaceDevice(int index, T newDevice)
        {
            this[index] = newDevice;
        }

        // Метод для перестановки товаров на витрине
        public void SwapDevices(int index1, int index2)
        {
            (this[index1], this[index2]) = (this[index2], this[index1]);
        }

        // Универсальная функция для поиска товара
        private int Find(DeviceCondition<T> condition)
        {
            for (int i = 0; i < devices.Length; i++)
            {
                if (condition(devices[i])) return i; // Возвращаем индекс первого подходящего устройства
            }
            return -1; // Если не найдено, возвращаем -1
        }

        // Метод для поиска товара по ID
        public int FindById(int deviceId)
        {
            return Find(device => device?.Id == deviceId);
        }

        // Метод для поиска товара по наименованию
        public int FindByName(string name)
        {
            return Find(device => string.Equals(device?.Name, name, StringComparison.OrdinalIgnoreCase));
        }

        // Универсальный метод для сортировки с использованием делегата
        private void Sort(CompareDevices<T> compare)
        {
            Array.Sort(devices, (p1, p2) => compare(p1, p2));
            UpdateBarcode();
        }

        // Метод для сортировки по ID
        public void SortById()
        {
            Sort((p1, p2) => (p1?.Id ?? int.MaxValue).CompareTo(p2?.Id ?? int.MaxValue));
        }

        // Метод для сортировки по наименованию
        public void SortByName()
        {
            Sort((p1, p2) => string.Compare(p1?.Name ?? "\uFFFF", p2?.Name ?? "\uFFFF", StringComparison.Ordinal));
        }

        public void Clear()
        {
            for (int i = 0; i < devices.Length; i++)
            {
                RemoveDevice(i);
            }
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

        // Метод для перемещения товара в другую витрину
        public void MoveDevice<TT>(T device, IShowcase<TT> targetShowcase) where TT : class, IDataDevice
        {
            if (device is not TT dev)
                return;
            // Добавление товара в другую витрину
            targetShowcase.AddDevice(dev);
            // Удаляем товар из текущей витрины
            RemoveDevice(FindById(device.Id));
        }

        // Обработчик события изменения ID устройства
        private void Device_IdChanged(object sender, EventArgs e)
        {
            if (sender is T device)
            {
                // Обновляем штрихкод при изменении ID устройства
                device.UpdateBarcode(this);
            }
        }
    }
}
