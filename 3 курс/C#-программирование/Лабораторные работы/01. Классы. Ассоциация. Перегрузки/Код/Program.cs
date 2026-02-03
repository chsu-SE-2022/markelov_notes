using BarcodeLibrary;

Barcode barcode = new("");

string text = "";
Console.WriteLine("Введите строку для кодировки: ");
while ((text = Console.ReadLine()).Length > 0)
{
    barcode.Text = text;
    Console.WriteLine(barcode);
    Console.WriteLine("Введите строку для кодировки: ");
