namespace BarcodeLibrary;

public class Barcode
{
    public Barcode(string text)
    {
        Text = text;
    }
    private string text;
    public string Text
    {
        get => text; // текущее значение text
        set
        {
            if (value == text) return; // Если совпадает с текущим значением - выходим

            text = value; // если нет - обновляем поле text
            Code = BarcodeHelper.GetCode(value);
        }
    }
    public string Code { get; private set; } // закодированное значение штрих-кода
    public static BarcodeType BarcodeType { get; set; } = BarcodeType.Full; // тип штрих-кода
    public override string ToString() // возвращает текст и/или штрих-код
    {
        return BarcodeType switch
        {
            BarcodeType.Barcode => Code,
            BarcodeType.Text => Text,
            _ => Code + "\n" + Text,
        };
    }

}
