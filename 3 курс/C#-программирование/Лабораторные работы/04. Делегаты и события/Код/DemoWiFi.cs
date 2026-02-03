using BarcodeLibrary;

namespace DataDevice
{
    public sealed class DemoWiFi : WiFi, IDataDevice
    {
        private BarcodeRecord barcode;
        private static BarcodeRecord bc = new("id");

        public DemoWiFi(int id, string name, double speed, double frequency, bool wireless)
            : base(id, name, speed, frequency, wireless)
        {
            barcode = new BarcodeRecord(id.ToString());
        }

        public override IBarcode Barcode => barcode;

        IBarcode IDataDevice.Barcode => bc;

        public override string ToString()
        {
            return $"{GetDeviceType()}: {Name}\n{GetCharacteristics()}\nШтрихкод:\n{barcode}\n";
        }
    }
}
