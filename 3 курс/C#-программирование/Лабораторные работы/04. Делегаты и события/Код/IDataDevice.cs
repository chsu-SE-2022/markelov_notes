using BarcodeLibrary;

namespace DataDevice;

public interface IDataDevice
{
    event EventHandler<IdChanged> IdChanged;  // Событие для изменения ID
    int Id { get; set; }
    string Name { get; set; }
    IBarcode Barcode { get; }
}