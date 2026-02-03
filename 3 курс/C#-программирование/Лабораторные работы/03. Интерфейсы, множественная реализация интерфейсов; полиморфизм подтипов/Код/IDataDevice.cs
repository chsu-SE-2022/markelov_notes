using BarcodeLibrary;

namespace DataDevice;

public interface IDataDevice
{
    int Id { get; set; }
    string Name { get; set; }
    IBarcode Barcode { get; }
}