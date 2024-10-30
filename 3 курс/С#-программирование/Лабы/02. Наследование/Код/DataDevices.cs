using BarcodeLibrary;
namespace DataDevices
{
    public abstract class DataDevices
    {
        private int id;

        public int Id
        {
            get => id;
            set
            {
                if (value == id) return;
                id = value;
                Barcode.Text = id.ToString();
            }
        }
        public string Name { get; set; }
        public Barcode Barcode { get; }
        protected DataDevices(int id, string name)
        {
            Barcode = new(id.ToString());
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
