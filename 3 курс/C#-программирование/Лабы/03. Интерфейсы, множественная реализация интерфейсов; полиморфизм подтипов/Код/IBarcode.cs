namespace BarcodeLibrary;

public interface IBarcode
{
    string Text { get; set; }
    string Code { get; }
    public static BarcodeType BarcodeType { get; set; } = BarcodeType.Full;
}