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
                id = value;
                if (Barcode != null)
                {
                    Barcode.Text = id.ToString();
                }
            }
        }

        public string Name { get; set; }
        public virtual IBarcode Barcode { get; }

        protected DataDevice(int id, string name)
        {
            Barcode = new Barcode(id.ToString());
            Id = id;
            Name = name;
        }

        protected abstract string GetDeviceType();
        protected abstract string GetCharacteristics();

        public override string ToString()
        {
            return $"{GetDeviceType()}: {Name}\n{GetCharacteristics()}\nШтрихкод:\n{Barcode}\n";
        }
    }
}
