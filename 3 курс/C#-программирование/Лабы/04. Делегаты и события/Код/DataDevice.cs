using BarcodeLibrary;

namespace DataDevice
{
    public abstract class DataDevice : IDataDevice
    {
        private int id;

        public int Id
        {
            get => id;
            set
            {
                if (value == id) return;
                int oldId = id; // Сохраняем старое значение ID
                id = value;
                if (Barcode != null)
                {
                    Barcode.Text = id.ToString();
                }
                OnIdChanged(new IdChanged(oldId, id)); // Вызываем событие изменения ID
            }
        }

        public string Name { get; set; }
        public virtual IBarcode Barcode { get; }

        public event EventHandler<IdChanged> IdChanged;  // Реализация события

        protected DataDevice(int id, string name)
        {
            Barcode = new Barcode(id.ToString());
            Id = id;
            Name = name;
        }

        protected abstract string GetDeviceType();
        protected abstract string GetCharacteristics();
        protected virtual void OnIdChanged(IdChanged e)
        {
            IdChanged?.Invoke(this, e);  // Генерация события
        }

        public override string ToString()
        {
            return $"{GetDeviceType()}: {Name}\n{GetCharacteristics()}\nШтрихкод:\n{Barcode}\n";
        }
    }
}
